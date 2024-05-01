""" Simple simulator to generate random samples.
"""

#!/usr/bin/env python3
from array import array
from logging import exception
import socket
import random
from sqlite3 import connect
import sys
from tokenize import Double
import numpy as np
from threading import Thread, Timer
import time

class Sensor(Thread):  
    
    def __init__(self,
        address: str,
        port: int,
        sampling_rate: int,
        _delay: float,
        _id: int) -> None:
        
        # Create a TCP/IP socket
        self.server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        # Define the server address and port
        self.server_address = (address, port)
        
        # Bind the server arg to the socket
        self.server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_sock.bind(self.server_address)
        # Listen for incoming connections
        self.server_sock.listen(1)

        print('_id', _id)

        print('sensor ' + str(_id) + ' listnening at ' + ' connecting to {} port {}'.format(*self.server_address))

        # This is an artificial delay we add as the over head
        self.overhead_delay = _delay 


        self.client_address = None
        self.sampling_rate = 0
        self.sensor_running = False
        self.connected = False
        self.DOF = 6
        self.sampling_rate = sampling_rate
        self.id = id

        sensor_thread = Thread(target = self.run)
        sensor_thread.daemon = True
        sensor_thread.start()
        

    def connect(self) -> bool:
        # Wait for a connection
            print('sensor ' + str(self.id) + ' waiting for a connection')
            while (self.client_address is None):
                self.client_connection, self.client_address = self.server_sock.accept()
            self.connected = True
            print('sensor ' + str(self.id) + ': connection from', self.client_address)
            return True

    def recive(self, buffer_size: int)->int:
        # Read a buffer size from the socket 
        recived_msg = self.client_connection.recv(buffer_size)
        msg = recived_msg.decode()
        if msg.isnumeric():
            return int(msg)
        else:
            print("recived a not numeric msg")



    def set_overhead(self, _delay: float) -> None:
        self.overhead_delay = _delay

    def set_sampling_rate(self, sampleing_rate: int) -> None:
        self.sampling_rate = sampleing_rate

    def send(self, data: np.ndarray)->bool:
        # Send the data to the client
        if self.connected:
            try:
                self.client_connection.sendall(data.tobytes())
                return True
            except:
                print("Something went wrong in sending samples to: ", self.client_address)
                return False

    def run(self):
            if self.connect():
                try:
                    while True:
                        # Recive the request for the number of samples
                        sample_length = self.recive(500)

                        print('Received sample_length ', sample_length)
                        # Let's pretend we are really collecting samples
                        time.sleep(int(sample_length)/self.sampling_rate + self.overhead_delay + random.randint(0, 100)/100000)
                        
                        # Send the samples to the client
                        self.send(np.random.rand(self.DOF, int(sample_length)))

                finally:
                    # Clean up the connection
                    self.client_connection.close()
                    self.server_sock.close() # Added: Close socket server as well
                    

def main(args=None):
    
    sensor1 = Sensor('127.0.0.1', 65432, 2000, 0.001) # Define a sensor with 2000Hz sampling rate and 1ms delay
    t1 = Thread(target = sensor1.run)
    t1.daemon = True

    ## you can also launch a second sensor
    sensor2 = Sensor('127.0.0.1', 60000, 4000, 0.003) # Define a sensor with 4000Hz sampling rate and 3ms delay
    t2 = Thread(target = sensor2.run)
    t2.daemon = True



    t1.start()
    t2.start()
    
    while True:
        pass
    
if __name__ == "__main__":
    main()
