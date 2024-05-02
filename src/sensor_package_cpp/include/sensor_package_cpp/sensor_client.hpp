#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/sensor_read.hpp"
#include <string>
#include <cstring>

#include "rclcpp/rclcpp.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <typeinfo>
using namespace std::chrono_literals;

class SensorClient: public rclcpp::Node {
private:
    rclcpp::CallbackGroup::SharedPtr callback_group;
    rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor_client;
    int sensor_id;
    int num_samples;
public:
    SensorClient(std::string name, int sensor_id, int num_samples)
        : Node(name)
        , sensor_id{sensor_id}
        , num_samples{num_samples}
        {
            // The clients are called within the publisher, so they must be in different Callback Groups than Publisher to avoid deadlock.
            // Clients 1 and 2 can be called in parallel, so place them in different Callback Groups as well.
            // Favoring MutuallyExclusive over Reentrant as it is safer: We then won't have two queries accessing same server data_reservoir.
            this->callback_group = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
            std::string client_name = std::string("sensor") + std::to_string(sensor_id) + "_read_service";
            RCLCPP_INFO(this->get_logger(), ("Initializing client: " + client_name).c_str());
            this->sensor_client = this->create_client<custom_interfaces::srv::SensorRead>(client_name, rmw_qos_profile_system_default, this->callback_group);
        }

    auto send_request()
    {
        RCLCPP_INFO(this->get_logger(), "Client: Send Request");

        // Make request
        rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedRequest request;
        request = std::make_shared<custom_interfaces::srv::SensorRead::Request>();
        request->num_samples = this->num_samples;


        while (!sensor_client->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), ("Client " + std::to_string(this->sensor_id) + ": Interrupted while waiting for the service.").c_str());
                rclcpp::shutdown();
            }
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Client " + std::to_string(this->sensor_id) + ": service not available, waiting again...").c_str());
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Client " + std::to_string(this->sensor_id) + " Connected to service").c_str());


        // Send request. Type of result_future: rclcpp::Client<custom_interfaces::srv::SensorRead>::FutureAndRequestId
        auto result_future = sensor_client->async_send_request(request);

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Client " + std::to_string(this->sensor_id) + ": Sent Request for " + std::to_string(this->num_samples) + " samples").c_str());

        // Must wait for result before Publisher takes our message, as we have allowed Publisher and Client to run concurrently in order to avoid deadlock. Timeout to guarantee a graceful finish
        std::future_status status = result_future.wait_for(10s);


        if (status == std::future_status::ready) {
            RCLCPP_INFO(this->get_logger(), ("Client " + std::to_string(this->sensor_id) + ": Received response").c_str());
        }
        if (status == std::future_status::timeout) {
            RCLCPP_INFO(this->get_logger(), ("Client " + std::to_string(this->sensor_id) + ": timeout").c_str());
        }
        if (status == std::future_status::deferred) {
            RCLCPP_INFO(this->get_logger(), ("Client " + std::to_string(this->sensor_id) + ": deferred").c_str());
        }

        return result_future.get();
    }
};
