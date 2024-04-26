#!/usr/bin/env python3

import sys

from custom_interfaces.srv import SensorRead 
import rclpy
from rclpy.node import Node


class SensorClient(Node):

    def __init__(self):
        super().__init__('sensor_client')
        self.cli = self.create_client(SensorRead, 'sensor_read_service')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = SensorRead.Request()

    def send_request(self, num_samples):
        self.req.num_samples = num_samples
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()
        


def main():
    rclpy.init()

    sensor_client = SensorClient()
    response = sensor_client.send_request(int(sys.argv[1]))
    print('all readings', response.readings)
    print('readings one by one')
    for i, datapoint in enumerate(response.readings):
        print(i, ' ', datapoint.data)
    sensor_client.get_logger().info(
        'num_samples sent: %d\ndata received: [redacted]' %
        int(sys.argv[1]))
    sensor_client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
