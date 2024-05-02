#include "custom_interfaces/msg/sensor_read_combined.hpp"
#include "sensor_client.hpp"

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
        RCLCPP_INFO(this->get_logger(), "Timer Publisher: Entered timer callback");

        // Query both Clients for sensor data
        // type i thought before: rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedResponse*
        auto result_sensor_1 = this->sensor1_client->send_request();
        auto result_sensor_2 = this->sensor2_client->send_request();

        RCLCPP_INFO(this->get_logger(), "Timer Publisher: Received responses from clients. Publishing");

        // Generate combined message
        custom_interfaces::msg::SensorReadCombined message = custom_interfaces::msg::SensorReadCombined();

        // Put Sensor 1 and Sensor 2 data into combined message
        message.readings_sensor1 = result_sensor_1->readings;
        message.readings_sensor2 = result_sensor_2->readings;
        message.num_datapoints1 = result_sensor_1->num_datapoints;
        message.num_datapoints2 = result_sensor_2->num_datapoints;

        // Publish
        publisher_->publish(message);
    }
    std::shared_ptr<SensorClient> sensor1_client;
    std::shared_ptr<SensorClient> sensor2_client;
    rclcpp::Publisher<custom_interfaces::msg::SensorReadCombined>::SharedPtr publisher_;
    int sensor1_num_samples;
    int sensor2_num_samples;
    rclcpp::CallbackGroup::SharedPtr callback_group;
    rclcpp::TimerBase::SharedPtr timer_;
public:
    SensorReadPublisher(std::shared_ptr<SensorClient> sensor1_client,
                        std::shared_ptr<SensorClient> sensor2_client,
                        int sensor1_num_samples,
                        int sensor2_num_samples)
            : Node("sensor_read_publisher")
            , sensor1_client {sensor1_client}
            , sensor2_client {sensor2_client}
            , publisher_ {this->create_publisher<custom_interfaces::msg::SensorReadCombined>("sensor_read_500hz", 10)}
            , sensor1_num_samples {sensor1_num_samples}
            , sensor2_num_samples {sensor2_num_samples}
    {
        // Callback group: MutuallyExclusive. Makes no sense to call a next timer sequence if our next one hasn't finished, although ideally this would never happen if our timer callback takes less than 2ms to run.
        this->callback_group = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
        this->timer_ = this->create_wall_timer(2ms, std::bind(&SensorReadPublisher::timer_callback, this), this->callback_group);
    }
};
