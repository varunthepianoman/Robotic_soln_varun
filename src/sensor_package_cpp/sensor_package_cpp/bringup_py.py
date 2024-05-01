#!/usr/bin/env python3

from sensor_package_cpp.submodules.sensor import Sensor
from sensor_package_cpp.submodules.sensor_service import SensorService
import rclpy


def main():
    rclpy.init()

    sensor1_service = SensorService(sensor_args = ['127.0.0.1', 65432, 2000, 0.001], number_of_samples=1)
    sensor2_service = SensorService(sensor_args = ['127.0.0.1', 77777, 4000, 0.003], number_of_samples=8)

    # Multi-threaded Executor.
    executor = rclpy.executors.MultiThreadedExecutor()

    # Add services to our executor.
    NOTE REMEMBER CALLBACKS
    executor.add_node(sensor1_service)
    executor.add_node(sensor2_service)




    rclpy.shutdown()


if __name__ == "__main__":
    main()