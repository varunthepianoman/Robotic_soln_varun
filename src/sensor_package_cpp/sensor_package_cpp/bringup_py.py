#!/usr/bin/env python3

from sensor_package_cpp.submodules.sensor import Sensor
from sensor_package_cpp.submodules.sensor_service import SensorService
import rclpy


def main():
    rclpy.init()

    address_1 = '127.0.0.1'
    address_2 = '127.0.0.2'
    port_1 = 65432
    port_2 = 60000
    sensor1_service = SensorService(address=address_1, port=port_1, sampling_rate=2000, _delay=0.001, sensor_id=1, number_of_samples=1)
    sensor2_service = SensorService(address=address_2, port=port_2, sampling_rate=4000, _delay=0.003, sensor_id=2, number_of_samples=8)

    # Multi-threaded Executor to allow parallel execution of services.
    executor = rclpy.executors.MultiThreadedExecutor()

    # Add services to our executor.
    executor.add_node(sensor1_service)
    executor.add_node(sensor2_service)

    # Spin executor
    executor.spin()

    # Shutdown
    rclpy.shutdown()


if __name__ == "__main__":
    main()
