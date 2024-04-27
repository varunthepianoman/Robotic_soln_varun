#include "custom_interfaces/msg/sensor_read_combined.hpp"
#include "sensor_client.cpp"

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class SensorReadPublisher : public rclcpp::Node
{
public:
    SensorReadPublisher(rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor_client_1, rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor_client_2, int sensor_1_num_samples, int sensor_2_num_samples)
            : Node("sensor_read_publisher"), count_(0)
    {
        self.sensor_client_1 = sensor_client_1;
        self.sensor_client_2 = sensor_client_2;
        self.sensor_1_num_samples = sensor_1_num_samples;
        self.sensor_2_num_samples = sensor_2_num_samples;
        publisher_ = this->create_publisher<custom_interfaces::msg::SensorReadCombined>("sensor_read_500hz", 10);
        timer_ = this->create_wall_timer(
                2ms, std::bind(&SensorReadPublisher::timer_callback, this));
    }

private:
    void timer_callback()
    {
        result_sensor_1 = self.sensor_client_1.send_request(self.sensor_1_num_samples);
        result_sensor_2 = self.sensor_client_2.send_request(self.sensor_2_num_samples);
        auto message = custom_interfaces::msg::SensorReadCombined();
        message.readings_sensor1 = result_sensor_1;
        message.readings_sensor2 = result_sensor_2;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s', and '%s'", message.readings_sensor1.c_str(), message.readings_sensor2.c_str());
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_; // CHANGE TYPE
    size_t count_;
}

// THIS WILL GO AWAY
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
    return 0;
}