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
            rclcpp::CallbackGroup::SharedPtr callback_group = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
            std::string client_name = std::string("sensor") + std::to_string(sensor_id) + "_read_service";
            this->sensor_client = this->create_client<custom_interfaces::srv::SensorRead>(client_name, rmw_qos_profile_system_default, callback_group);
        }

    auto send_request()
    {
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


        // rclcpp::Client<custom_interfaces::srv::SensorRead>::FutureAndRequestId
        auto result_future = sensor_client->async_send_request(request);

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Client " + std::to_string(this->sensor_id) + ": Sent Request for " + std::to_string(this->num_samples) + " samples").c_str());

        // Must wait for result as we have allowed Publisher and Client to run concurrently (in order to avoid deadlock). Timeout to guarantee a graceful finish
        std::future_status status = result_future.wait_for(1s);

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Client " + std::to_string(this->sensor_id) + ": After future wait_for").c_str());

        if (status == std::future_status::ready) {
            RCLCPP_INFO(this->get_logger(), ("Client " + std::to_string(this->sensor_id) + ": Received response").c_str());
        }

        // const rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedResponse
        //auto result_future_shared = result_future//.future.share();

        // Curiously, the SharedResponse object seems to have overloaded the address-of (&) operator. I tried to return a pointer to the SharedResponse object and extract readings in the Publisher, but it gave me and allocator instead of an address.
        // So, I just extract the readings here and return a pointer to them.
        // Type I thought before: custom_interfaces::msg::SensorSample[]
        const auto readings_output = result_future.get()->readings;

//        std::cout << "readings" <<  readings_output

//        auto test_addr = &result_future_get;
//
//        auto readings_sensor1_after_addressing = test_addr->readings;
//        auto readings_sensor1_after_addressing_and_deref = (*test_addr)->readings;

        // NOTE: Remember to handle zero-data case!
        return readings_output;
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
