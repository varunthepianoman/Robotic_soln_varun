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
private:
    void timer_callback()
    {
        // Query both Clients for sensor data
        rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedResponse* result_sensor_1 = this->sensor1_client->send_request();
        rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedResponse* result_sensor_2 = this->sensor2_client->send_request();

        // Generate combined message
        custom_interfaces::msg::SensorReadCombined message = custom_interfaces::msg::SensorReadCombined();

        // Put Sensor 1 and Sensor 2 data into combined message
        rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedResponse deref_result1 = (*result_sensor_1);

        // message.readings_sensor1 = deref_result1->readings;
        // message.readings_sensor2 = result_sensor_2.readings;

        // Publish combined message
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s', and '%s'", message.readings_sensor1.std::string::c_str(), message.readings_sensor2.std::string::c_str());
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<custom_interfaces::msg::SensorReadCombined>::SharedPtr publisher_;
    SensorClient* sensor1_client;
    SensorClient* sensor2_client;
    int sensor1_num_samples;
    int sensor2_num_samples;
public:
    SensorReadPublisher(rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor1_client, rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor2_client, int sensor1_num_samples, int sensor2_num_samples)
            : Node("sensor_read_publisher")
            , sensor1_client {sensor1_client}
            , sensor2_client {sensor2_client}
            , publisher_ {this->create_publisher<custom_interfaces::msg::SensorReadCombined>("sensor_read_500hz", 10)}
            , timer_ {this->create_wall_timer(2ms, std::bind(&SensorReadPublisher::timer_callback, this))}
            , sensor1_num_samples {sensor1_num_samples}
            , sensor2_num_samples {sensor2_num_samples}
    {
    }

};

// THIS WILL GO AWAY
//int main(int argc, char * argv[])
//{
//    rclcpp::init(argc, argv);
//    rclcpp::spin(std::make_shared<MinimalPublisher>());
//    rclcpp::shutdown();
//    return 0;
//}