#include "sensor_package_cpp/sensor_read_publisher.hpp"
#include "sensor_package_cpp/sensor_read_subscriber.hpp"
#define CLIENT1_NUM_SAMPLES 2
#define CLIENT2_NUM_SAMPLES 8

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    // Make a MultiThreadedExecutor to allow threads to run in parallel.
    rclcpp::executors::MultiThreadedExecutor executor;

    // make 2 SensorClient objects, one for each sensor.
    SensorClient sensor1_client = std::make_shared<SensorClient>("sensor1_client", CLIENT1_NUM_SAMPLES);
    SensorClient sensor2_client = std::make_shared<SensorClient>("sensor2_client", CLIENT2_NUM_SAMPLES);

    // make SensorReadPublisher
    publisher = std::make_shared<SensorReadPublisher>(sensor1_client, sensor2_client, CLIENT1_NUM_SAMPLES, CLIENT2_NUM_SAMPLES);

    // make SensorReadSubscriber
    subscriber = std::make_shared<SensorReadSubscriber>();

    // Add all 4 nodes to our executor
    executor.add_node(client1_node);
    executor.add_node(client2_node);
    executor.add_node(publisher);
    executor.add_node(subscriber);

    // Start our executor
    executor.spin();

    return 0;

}
