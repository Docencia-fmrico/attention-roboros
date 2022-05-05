#include "rclcpp/rclcpp.hpp"
#include "attention_roboros/GazeboGraph.cpp"

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto graph_node = std::make_shared<GazeboGraph>();
    //auto node_neck = std::make_shared<NeckController>();
    rclcpp::spin(graph_node);
    //rclcpp::spin(node_neck);
    rclcpp::shutdown();
    return 0;
}