#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/sensor_read_combined.hpp"
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

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
    void topic_callback(const std_msgs::msg::String & msg) const
    {
        RCLCPP_INFO(this->get_logger(), "Heard");
        std::cout << msg
    }
    rclcpp::Subscription<custom_interfaces::msg::SensorReadCombined>::SharedPtr subscription_;
};

//int main(int argc, char * argv[])
//{
//    rclcpp::init(argc, argv);
//    rclcpp::spin(std::make_shared<MinimalSubscriber>());
//    rclcpp::shutdown();
//    return 0;
//}

