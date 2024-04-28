#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/sensor_read.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <typeinfo>
using namespace std::chrono_literals;

// Below is a wrapper class for an already-created node and client: We use this class to call the service.
class SensorClient {
private:
    std::shared_ptr <rclcpp::Node> node;
    rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor_client;
public:
    SensorClient(std::shared_ptr <rclcpp::Node> node,
                 rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor_client) : {
        this->node = node;
        this->sensor_client = sensor_client;
    }

    &custom_interfaces::srv::SensorRead::Response send_request(int num_samples):
    {
        auto request = std::make_shared<custom_interfaces::srv::SensorRead::Request>();
        request->num_samples = num_samples

        while (!sensor_client->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
                return 0;
            }
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
        }

        auto result = sensor_client->async_send_request(request);

        return result;
//        // Handled by my callback groups! Wait for the result.
//        if (rclcpp::spin_until_future_complete(node, result) ==
//            rclcpp::FutureReturnCode::SUCCESS) {
//            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Data received: [redacted]");
//        } else {
//            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service sensor_read_service");
//        }
    }
};
//    std::cout << "type(result)" << typeid(result).name();
//	std::cout << "\n\n\n";
//    rclcpp::shutdown();
//    return 0;

