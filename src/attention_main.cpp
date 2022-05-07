#include "rclcpp/rclcpp.hpp"

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    //auto node_neck = std::make_shared<NeckController>();
    //rclcpp::spin(node_neck);
    rclcpp::shutdown();
    return 0;
}