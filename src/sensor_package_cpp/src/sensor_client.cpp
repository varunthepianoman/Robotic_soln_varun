#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/sensor_read.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <typeinfo>
using namespace std::chrono_literals;

int main(int argc, char **argv)
{
    std::cout << "first line of main";
	rclcpp::init(argc, argv);
	std::cout << "after init";	

	std::cout << "before make node";
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("sensor_client_node");

	std::cout << "before make client";
    rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor_client =
            node->create_client<custom_interfaces::srv::SensorRead>("sensor_read_service");
	std::cout << "after make client";

    auto request = std::make_shared<custom_interfaces::srv::SensorRead::Request>();
    request->num_samples = atoll(argv[1]);

	std::cout << 28;
    while (!sensor_client->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return 0;
	} 
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

	std::cout << 37;
    auto result = sensor_client->async_send_request(request);

	std::cout << 40;
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Data received: [redacted]");
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service sensor_read_service");
    }
    std::cout << "type(result)" << typeid(result).name();
	std::cout << "\n\n\n";
    rclcpp::shutdown();
    return 0;
}
