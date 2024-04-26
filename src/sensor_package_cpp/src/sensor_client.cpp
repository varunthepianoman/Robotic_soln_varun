#include "rclcpp/rclcpp.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    if (argc != 3) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: unsure");
        return 1;
    }

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("sensor_client_node");
    rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor_client =
            node->create_client<custom_interfaces::srv::SensorRead>("sensor_read_service");

    auto request = std::make_shared<custom_interfaces::srv::SensorRead::Request>();
    request->num_samples = atoll(argv[1]);

    while (!client->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = client->async_send_request(request);
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Data received: [redacted]");
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service sensor_read_service");
    }

    rclcpp::shutdown();
    return 0;
}