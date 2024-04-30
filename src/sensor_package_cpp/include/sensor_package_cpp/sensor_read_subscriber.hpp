#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/sensor_read_combined.hpp"
#include "std_msgs/msg/string.hpp"
#include<cstring>
#include<string>

#include <iostream>
using std::placeholders::_1;

class SensorReadSubscriber : public rclcpp::Node
{
public:
    SensorReadSubscriber()
            : Node("sensor_read_subscriber")
    {
        // Configure SubscriptionOptions to assign a new callback group for SubscriptionOptions so it can be run in parallel to Publisher.
        rclcpp::SubscriptionOptions options;
        options.callback_group = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

        subscription_ = this->create_subscription<custom_interfaces::msg::SensorReadCombined>(
                 "sensor_read_500hz", 10, std::bind(&SensorReadSubscriber::topic_callback, this, _1), options);

    }

private:
    rclcpp::Subscription<custom_interfaces::msg::SensorReadCombined>::SharedPtr subscription_;
    void topic_callback(const custom_interfaces::msg::SensorReadCombined & msg) const
    {
        RCLCPP_INFO(this->get_logger(), "Heard");
        const std::shared_ptr<rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample>> sensor1_data = std::make_shared<rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample>>>(msg.readings_sensor1);
        const std::shared_ptr<rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample>> sensor2_data = std::make_shared<rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample>>>(msg.readings_sensor2);
        RCLCPP_INFO(this->get_logger(), "Sensor 1 Data:\n");
        print_sensor_sample(sensor1_data);
        RCLCPP_INFO(this->get_logger(), "Sensor 2 Data:\n");
        print_sensor_sample(sensor2_data);
    }

    void print_sensor_sample(const std::shared_ptr<rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample>>> sensor_data) const
    {
        for (custom_interfaces::msg::SensorSample sample : sensor_data) {
            std::string sample_line = "Sample " + std::to_string(i) + ": "
            RCLCPP_INFO(this->get_logger(), sample_line);
            std::string data_line = "[";
            for (double datapoint : sample.data) {
                data_line += std::to_string(datapoint) + " "
            }
            std::string data_line += "]";
            RCLCPP_INFO(this->get_logger(), data_line);
        }
    }
};

//int main(int argc, char * argv[])
//{
//    rclcpp::init(argc, argv);
//    rclcpp::spin(std::make_shared<MinimalSubscriber>());
//    rclcpp::shutdown();
//    return 0;
//}

