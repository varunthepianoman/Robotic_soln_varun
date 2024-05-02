#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/sensor_read_combined.hpp"
#include "std_msgs/msg/string.hpp"
#include <cstring>
#include <string>

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
        std::shared_ptr<const rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample, 8>> sensor1_data = msg.readings_sensor1;
        std::shared_ptr<const rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample, 8>> sensor2_data = msg.readings_sensor2;
        std::shared_ptr<int> sensor1_num_datapoints = msg.num_datapoints1
        std::shared_ptr<int> sensor2_num_datapoints = msg.num_datapoints2
        RCLCPP_INFO(this->get_logger(), "Sensor 1 Data:\n");
        print_sensor_sample<8>(sensor1_data, *sensor1_num_datapoints);
        RCLCPP_INFO(this->get_logger(), "Sensor 2 Data:\n");
        print_sensor_sample<8>(sensor2_data, *sensor2_num_datapoints);
    }

    template<int N> // N = Maximum length of samples.
    void print_sensor_sample(std::shared_ptr<const rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample, N>> sensor_data,
                             int num_datapoints) const
    {
        int i = 0;
        for (custom_interfaces::msg::SensorSample sample : *sensor_data) {
            assert(i <= num_datapoints)
            std::string sample_line = "Sample " + std::to_string(i) + ": ";
            RCLCPP_INFO(this->get_logger(), sample_line.c_str());
            std::string data_line = "[";
            for (double datapoint : sample.data) {
                data_line += std::to_string(datapoint) + " ";
            }
            data_line += "]";
            RCLCPP_INFO(this->get_logger(), data_line.c_str());
            i++;
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

