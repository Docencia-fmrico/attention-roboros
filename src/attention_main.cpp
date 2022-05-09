#include "rclcpp/rclcpp.hpp"

#include "attention_roboros/GazeboGraph.cpp"

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    GazeboGraph grafo;
    grafo.add_node("Pepe","Mesa");
    grafo.add_node("Rober","Mesa");
    grafo.add_node("Andres","Mesa");
    //rclcpp::spin(node_neck);
    //auto node_neck = std::make_shared<NeckController>();
    //rclcpp::spin(node_neck);
    rclcpp::shutdown();
    return 0;
}