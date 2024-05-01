#!/usr/bin/env python3

from custom_interfaces.srv import SensorRead
from custom_interfaces.msg import SensorSample
from collections import deque
import rclpy
from rclpy.node import Node
import numpy as np
from sensor_package_cpp.submodules.sensor import Sensor
import socket
import sys
import time
from threading import Thread, Timer
from multiprocessing import Process


buffer_size = 32 # How many sensor samples to store in our buffer: We need 2 maximum for sensor1 and 8 maximum for sensor2. Store 32 for safety.


class SensorService(Node):

    def __init__(self, sensor_args, number_of_samples):
        super().__init__('sensor_service')
        # Callback groups: Services can run in parallel so put each in its own callback group.
        # Use MutuallyExclusiveCallback instead of Reentrant so that we ensure that the earliest call gets the earliest data for publishing.
        # (We are unlikely to have multiple queued callbacks as our timer publisher runs only every 2ms.)
        service_callback_group = rclpy.callback_groups.MutuallyExclusiveCallbackGroup()

        self.srv = self.create_service(SensorRead, 'sensor_read_service', self.sensor_read_callback, callback_group=service_callback_group)
        self.sensor = Sensor(**sensor_args) # Define a sensor with 2000Hz sampling rate and 1ms delay
        self.number_of_samples = number_of_samples

        # Separate thread for sensor querying is required: if not, we will get stuck in the "while True" loop querying for sensor samples.
        # threading.Thread solves this problem. However, prefer multiprocessing.Process because: due to Python's Global Interpreter Lock, threads without Multiprocessing run serially. multiprocessing allows the use of multiple cores and truly parallel threads that run on different cores.
        sensor_thread = Process(target = self.query_for_samples)
        sensor_thread.daemon = True
        sensor_thread.start()

        self.data_reservoir = deque(maxlen=buffer_size) # Data reservoir is a reservoir of the last 200 samples.

        # Create a TCP/IP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect the socket to the port where the server is listening
        server_address = ('127.0.0.1', 65432)
        print('connecting to {} port {}'.format(*server_address))
        self.sock.connect(server_address)
        print('connected')

    def sensor_read_callback(self, request, response):
        # Request num_samples samples from the sensor
        # TODO: Wait if there are not enough samples left!
        # time.sleep(5)
        print('entered sensor callback')
        print('request.num_samples', request.num_samples)
        print('len(data)', len(self.data_reservoir))
        Sensor_Samples = []
        zero_data = True # A variable that tracks special case when we have no data
        for i in range(request.num_samples):
            datapoint = SensorSample()
            # Try to pop() from self.data_reservoir: IndexError means no more data in buffer and we construct our SampleSet and return.
            try:
                datapoint.data = self.data_reservoir.pop()
            except IndexError:
                break
            zero_data = False
            Sensor_Samples.append(datapoint)
        response.readings = Sensor_Samples
        response.zero_data = zero_data
        print('response after generating', response.readings)
        return response

    def query_for_samples(self):
        sensor_dof = self.sensor.DOF # For fast access
        while True:
            message_string = str(self.number_of_samples)
            message = message_string.encode()
            self.sock.sendall(message)

            byte_data = self.sock.recv(10000)
            sensor_data = np.frombuffer(byte_data)
            sensor_data = sensor_data.reshape(self.number_of_samples, sensor_dof)
            for datapoint in sensor_data:
                self.data_reservoir.append(datapoint) # List appending takes about same time as editing preallocated numpy array: Append to list for simplicity



def main():
    rclpy.init()

    sensor_service = SensorService()

    rclpy.spin(sensor_service)

    rclpy.shutdown()


if __name__ == '__main__':
    main()
