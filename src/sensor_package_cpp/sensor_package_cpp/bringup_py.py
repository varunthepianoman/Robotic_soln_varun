#!/usr/bin/env python3

from sensor_package_cpp.submodules.sensor import Sensor
from sensor_package_cpp.submodules.sensor_service import SensorService
import rclpy


def main():
    rclpy.init()

    sensor1_service = SensorService(address='127.0.0.1', port=65432, sampling_rate=2000, _delay=0.001, sensor_id=1, number_of_samples=1)
    sensor2_service = SensorService(address='127.0.0.1', port=60000, sampling_rate=4000, _delay=0.003, sensor_id=2, number_of_samples=8)

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