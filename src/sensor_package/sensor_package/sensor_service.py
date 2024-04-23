from tutorial_interfaces.srv import SensorRead
from tutorial_interfaces.msg import SensorSample

import rclpy
from rclpy.node import Node
import numpy as np

class SensorService(Node):

    def __init__(self):
        super().__init__('sensor_service')
        self.srv = self.create_service(SensorRead, 'sensor_read_service', self.sensor_read_callback)

    def sensor_read_callback(self, request, response):
        sensor_data = np.random.rand(6, request.num_samples)
        Sensor_Samples = []
        for i in range(request.num_samples):
            datapoint = SensorSample()
            datapoint.data = sensor_data[:,i]
            Sensor_Samples.append(datapoint)
        response.readings = Sensor_Samples
        return response

def main():
    rclpy.init()

    minimal_service = SensorService()

    rclpy.spin(sensor_service)

    rclpy.shutdown()


if __name__ == '__main__':
    main()
