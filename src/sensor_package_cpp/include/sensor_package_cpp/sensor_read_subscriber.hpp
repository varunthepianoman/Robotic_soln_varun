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
        const std::shared_ptr<std::vector<std::vector<double>>> sensor1_data = std::make_shared<std::vector<std::vector<double>>>(msg.readings_sensor1);
        const std::shared_ptr<std::vector<std::vector<double>>> sensor2_data = std::make_shared<std::vector<std::vector<double>>>(msg.readings_sensor2);
        RCLCPP_INFO(this->get_logger(), "Sensor 1 Data:\n");
        print_sensor_sample(sensor1_data);
        RCLCPP_INFO(this->get_logger(), "Sensor 2 Data:\n");
        print_sensor_sample(sensor2_data);
    }

    void print_sensor_sample(const std::shared_ptr<std::vector<std::vector<double>>> sensor_data) const
    {
        for (int i = 0; i < sizeof(sensor_data); i++) {
            RCLCPP_INFO(this->get_logger(), "Sample ".c_str());
            RCLCPP_INFO(this->get_logger(), i.c_str());
            RCLCPP_INFO(this->get_logger(), ": ".c_str());
            for (int j = 0; j < 6; j++) {
                RCLCPP_INFO(this->get_logger(), sensor_data[i][j].c_str());
            }
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

