#include "sensor_client.cpp"
#include "sensor_read_publisher.cpp"
#include "sensor_read_subscriber.cpp"
#define CLIENT1_NUM_SAMPLES 2
#define CLIENT2_NUM_SAMPLES 8

int main() {
    rclcpp::init(argc, argv);

    rclcpp::executors::MultiThreadedExecutor executor;

    // The clients are called within the publisher, so they must be in different Callback Groups to avoid deadlock.
    // Clients 1 and 2 can be called in parallel, so place them in different Callback Groups as well.
    // Favoring MutuallyExclusive over Reentrant as it is safer: We then won't have two queries accessing same server data_reservoir.
    client1_callback_group = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    client2_callback_group = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    publisher_callback_group = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    subscriber_callback_group = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);


    // node for clients 1 and 2
    std::shared_ptr <rclcpp::Node> client1_node = rclcpp::Node::make_shared("sensor1_client_node");
    std::shared_ptr <rclcpp::Node> client2_node = rclcpp::Node::make_shared("sensor2_client_node");

    // make clients in nodes
    rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor1_client =
            client1_node->create_client<custom_interfaces::srv::SensorRead>("sensor1_read_service", rclcpp::QoS(10), client1_callback_group);
    rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor2_client =
            client2_node->create_client<custom_interfaces::srv::SensorRead>("sensor2_read_service", rclcpp::QoS(10), client2_callback_group));

    // make publisher
    publisher = std::make_shared<SensorReadPublisher>(sensor1_client, sensor2_client, CLIENT1_NUM_SAMPLES, CLIENT2_NUM_SAMPLES);

    // make subscriber
    subscriber = std::make_shared<SensorReadSubscriber>();

    executor.add_node(client1_node);
    executor.add_node(client2_node);
    executor.add_node(publisher);
    executor.add_node(subscriber);

    executor.spin();

}