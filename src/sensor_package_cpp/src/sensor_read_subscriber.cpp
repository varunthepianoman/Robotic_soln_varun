#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/sensor_read_combined.hpp"
using std::placeholders::_1;

class SensorReadSubscriber : public rclcpp::Node
{
public:
    SensorReadSubscriber()
            : Node("sensor_read_subscriber")
            , subscription_ = this->create_subscription<custom_interfaces::msg::SensorReadCombined>(
                "sensor_read_500hz", 10, std::bind(&SensorReadSubscriber::topic_callback, this, _1));
    {
    }

private:
    void topic_callback(const std_msgs::msg::String & msg) const
    {
        RCLCPP_INFO(this->get_logger(), "Heard");
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

//int main(int argc, char * argv[])
//{
//    rclcpp::init(argc, argv);
//    rclcpp::spin(std::make_shared<MinimalSubscriber>());
//    rclcpp::shutdown();
//    return 0;
//}

int main() {}