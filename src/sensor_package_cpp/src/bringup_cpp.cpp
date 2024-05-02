#include "sensor_package_cpp/sensor_read_publisher.hpp"
#include "sensor_package_cpp/sensor_read_subscriber.hpp"
#include "rclcpp/rclcpp.hpp"
#include <iostream>
#define CLIENT1_NUM_SAMPLES 100//2
#define CLIENT2_NUM_SAMPLES 100//8

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    // Make a MultiThreadedExecutor to allow threads to run in parallel.
    rclcpp::executors::MultiThreadedExecutor executor;

    // make 2 SensorClient objects, one for each sensor.
    std::shared_ptr<SensorClient> sensor1_client = std::make_shared<SensorClient>("sensor1_client", 1, CLIENT1_NUM_SAMPLES);
    std::shared_ptr<SensorClient> sensor2_client = std::make_shared<SensorClient>("sensor2_client", 2, CLIENT2_NUM_SAMPLES);

    // make SensorReadPublisher
    std::shared_ptr<SensorReadPublisher> publisher = std::make_shared<SensorReadPublisher>(sensor1_client, sensor2_client, CLIENT1_NUM_SAMPLES, CLIENT2_NUM_SAMPLES);

    // make SensorReadSubscriber
    std::shared_ptr<SensorReadSubscriber> subscriber = std::make_shared<SensorReadSubscriber>();

    // Add all 4 nodes to our executor
    executor.add_node(sensor1_client);
    executor.add_node(sensor2_client);
    executor.add_node(publisher);
    executor.add_node(subscriber);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "bringup_cpp: About to spin");

    // Start our executor
    executor.spin();

    // Shutdown
    rclcpp::shutdown();

    return 0;

}
