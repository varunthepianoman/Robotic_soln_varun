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


buffer_size = 32 # How many sensor samples to store in our buffer: We need 2 maximum for sensor1 and 8 maximum for sensor2. Store 32 for safety.


class SensorService(Node):

    def __init__(self,
                 address: str,
                 port: int,
                 sampling_rate: int,
                 _delay: float,
                 sensor_id: int,
                 number_of_samples: int):
        super().__init__('sensor_service_' + str(sensor_id))
        # Callback groups: Services can run in parallel so put each in its own callback group.
        # Use MutuallyExclusiveCallback instead of Reentrant so that we ensure that the earliest call gets the earliest data for publishing.
        # (We are unlikely to have multiple queued callbacks as our timer publisher runs only every 2ms.)
        service_callback_group = rclpy.callback_groups.MutuallyExclusiveCallbackGroup()

        self.srv = self.create_service(SensorRead, 'sensor_read_service', self.sensor_read_callback, callback_group=service_callback_group)
        self.sensor = Sensor(address, port, sampling_rate, _delay, id) # Define a sensor with sampling rate and delay defined in constructor args
        self.sensor_id = sensor_id
        self.number_of_samples = number_of_samples

        # Separate thread for sensor querying is required: if not, we will get stuck in the "while True" loop querying for sensor samples.
        # threading.Thread solves this problem.
        sensor_thread = Thread(target = self.query_for_samples)
        sensor_thread.daemon = True
        sensor_thread.start()

        self.data_reservoir = deque(maxlen=buffer_size) # Data reservoir is a deque reservoir of the last buffer_size samples.

        # Create a TCP/IP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect the socket to the port where the server is listening
        server_address = (address, port)
        print('connecting to {} port {}'.format(*server_address))
        self.sock.connect(server_address)
        print('connected')

    def sensor_read_callback(self, request, response):
        # Request num_samples samples from the sensor
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
        while True:
            message_string = str(self.number_of_samples)
            message = message_string.encode()
            breakpoint()
            self.sock.sendall(message)

            byte_data = self.sock.recv(10000)
            sensor_data = np.frombuffer(byte_data)
            sensor_data = sensor_data.reshape(self.number_of_samples, self.sensor.DOF)
            for datapoint in sensor_data:
                self.data_reservoir.append(datapoint) # List appending takes about same time as editing preallocated numpy array: Append to list for simplicity



def main():
    rclpy.init()

    sensor_service = SensorService()

    rclpy.spin(sensor_service)

    rclpy.shutdown()


if __name__ == '__main__':
    # Main script
    main()
