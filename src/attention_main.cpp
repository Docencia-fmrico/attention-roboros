#include "rclcpp/rclcpp.hpp"

#include "attention_roboros/GazeboGraph.cpp"

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node_neck = std::make_shared<GazeboGraph>();
    //rclcpp::spin(node_neck);
    //auto node_neck = std::make_shared<NeckController>();
    //rclcpp::spin(node_neck);
    rclcpp::shutdown();
    return 0;
}