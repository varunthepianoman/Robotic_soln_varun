#include "sensor_package_cpp/sensor_read_publisher.hpp"
#include "sensor_package_cpp/sensor_read_subscriber.hpp"
#define CLIENT1_NUM_SAMPLES 2
#define CLIENT2_NUM_SAMPLES 8

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    rclcpp::executors::MultiThreadedExecutor executor;

    // make subscriber

//    short_subscriber_ = create_subscription<std_msgs::msg::String>(
//            "/short_topic", rclcpp::QoS(10),
//            std::bind(&MultiThreadMutuallyExclusiveSubscriber::ShortTopicCallback,
//                      this, std::placeholders::_1),
//            options);

    //  Create client objects
    // node for clients 1 and 2
    std::shared_ptr <rclcpp::Node> client1_node = rclcpp::Node::make_shared("sensor1_client_node");

    SensorClient sensor1_client = SensorClient("sensor1_client", CLIENT1_NUM_SAMPLES)
    SensorClient sensor2_client = SensorClient("sensor2_client", CLIENT2_NUM_SAMPLES)

    // make clients in nodes
    rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor1_client =
            client1_node->create_client<custom_interfaces::srv::SensorRead>("sensor1_read_service", rclcpp::QoS(10), client1_callback_group);
    rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor2_client =
            client2_node->create_client<custom_interfaces::srv::SensorRead>("sensor2_read_service", rclcpp::QoS(10), client2_callback_group));

    // make publisher: Remember to put Pointers to clients
    publisher = std::make_shared<SensorReadPublisher>(sensor1_client, sensor2_client, CLIENT1_NUM_SAMPLES, CLIENT2_NUM_SAMPLES);

    subscriber = std::make_shared<SensorReadSubscriber>();

    executor.add_node(client1_node);
    executor.add_node(client2_node);
    executor.add_node(publisher);
    executor.add_node(subscriber);

    executor.spin();

    return 0;

}
