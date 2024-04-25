from custom_interfaces.srv import SensorRead
from custom_interfaces.msg import SensorSample

import rclpy
from rclpy.node import Node
import numpy as np
from sensor import Sensor
import socket
import sys
import time


class SensorService(Node):

    def __init__(self):
        super().__init__('sensor_service')
        self.srv = self.create_service(SensorRead, 'sensor_read_service', self.sensor_read_callback)
        self.sensor = Sensor('127.0.0.1', 65432, 2000, 0.001) # Define a sensor with 2000Hz sampling rate and 1ms delay
        
        # Create a TCP/IP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect the socket to the port where the server is listening
        server_address = ('127.0.0.1', 65432)
        print('connecting to {} port {}'.format(*server_address))
        sock.connect(server_address)

    def sensor_read_callback(self, request, response):
        # Request num_samples samples from the sensor
        message_string = str(request.num_samples)
        message = message_string.encode()
        sock.sendall(message)

        byte_data = sock.recv(10000)
        sensor_data = np.frombuffer(byte_data) 


        Sensor_Samples = []
        for i in range(request.num_samples):
            datapoint = SensorSample()
            datapoint.data = sensor_data[:,i]
            Sensor_Samples.append(datapoint)
        response.readings = Sensor_Samples
        return response

def main():
    rclpy.init()

    sensor_service = SensorService()

    rclpy.spin(sensor_service)

    rclpy.shutdown()


if __name__ == '__main__':
    main()
