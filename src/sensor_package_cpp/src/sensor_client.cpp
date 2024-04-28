#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/sensor_read.hpp"
#include <rclcpp/client.hpp>
#include <string>


#include <chrono>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <typeinfo>
using namespace std::chrono_literals;

class SensorClient: public rclcpp::Node {
private:
    rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor_client;
    int num_samples;
public:
    SensorClient(std::string name, int num_samples)
        : Node(name)
        , num_samples{num_samples}
        {
            // The clients are called within the publisher, so they must be in different Callback Groups than Publisher to avoid deadlock.
            // Clients 1 and 2 can be called in parallel, so place them in different Callback Groups as well.
            // Favoring MutuallyExclusive over Reentrant as it is safer: We then won't have two queries accessing same server data_reservoir.

            rclcpp::CallbackGroup::SharedPtr callback_group = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
            rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr client = this->create_client<custom_interfaces::srv::SensorRead>("sensor1_read_service", rmw_qos_profile_system_default, callback_group);
        }

    (rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedResponse)* send_request()
    {
        rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedRequest request;
        request = std::make_shared<custom_interfaces::srv::SensorRead::Request>();
        request->num_samples = this->num_samples;

        while (!sensor_client->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
                return 0;
            }
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
        }

        rclcpp::Client<custom_interfaces::srv::SensorRead>::FutureAndRequestId result_future = sensor_client->async_send_request(request);

        // Must wait for result as we have allowed Publisher and Client to run concurrently (in order to avoid deadlock). Timeout to guarantee a graceful finish
        std::future_status status = result_future.wait_for(1s);

        if (status == std::future_status::ready) {
            RCLCPP_INFO(this->get_logger(), "Received response");
        }

        return &(result_future.get());
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

