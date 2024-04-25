from custom_interfaces.srv import SensorRead
from custom_interfaces.msg import SensorSample
from collections import deque
import rclpy
from rclpy.node import Node
import numpy as np
from .submodules.sensor import Sensor
import socket
import sys
import time
from threading import Thread, Timer

# requesting 10 samples on each call
number_of_samples = 10

buffer_size = 200 # How many sensor samples to store in our buffer: 200 samples should be more than enough space for our purposes.


class SensorService(Node):

    def __init__(self):
        super().__init__('sensor_service')
        self.srv = self.create_service(SensorRead, 'sensor_read_service', self.sensor_read_callback)
        self.sensor = Sensor('127.0.0.1', 65432, 2000, 0.001) # Define a sensor with 2000Hz sampling rate and 1ms delay
        t1 = Thread(target = self.sensor.run)
        t1.daemon = True
        t1.start()

        self.data_reservoir = deque(maxlen=buffer_size) # Data reservoir is a reservoir of the last 200 samples.

        # Create a TCP/IP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect the socket to the port where the server is listening
        server_address = ('127.0.0.1', 65432)
        print('connecting to {} port {}'.format(*server_address))
        self.sock.connect(server_address)
        print('connected')

        t2 = Thread(target=self.query_for_samples)
        t2.daemon = True
        t2.start()

    def sensor_read_callback(self, request, response):
        # Request num_samples samples from the sensor
        # TODO: Wait if there are not enough samples left!
        # time.sleep(5)
        Sensor_Samples = []
        for i in range(request.num_samples):
            datapoint = SensorSample()
            datapoint.data = self.data_reservoir.pop()
            Sensor_Samples.append(datapoint)
        response.readings = Sensor_Samples
        return response

    def query_for_samples(self):
        sensor_dof = self.sensor.DOF # For fast access
        while True:
            print('in forever loop')
            print('data_reservoir', self.data_reservoir)
            message_string = str(number_of_samples)
            message = message_string.encode()
            self.sock.sendall(message)

            byte_data = self.sock.recv(10000)
            sensor_data = np.frombuffer(byte_data)
            sensor_data = sensor_data.reshape(number_of_samples, sensor_dof)
            for datapoint in sensor_data:
                self.data_reservoir.append(datapoint) # List appending takes about same time as editing preallocated numpy array: Append to list for simplicity



def main():
    rclpy.init()

    sensor_service = SensorService()

    rclpy.spin(sensor_service)

    rclpy.shutdown()


if __name__ == '__main__':
    main()
