#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "iostream"

#include "attention_roboros/GraphClient.cpp"


int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<GraphClient>();
    node->crear_garfo();

    //RCLCPP_INFO(node->get_logger(), "Hola" );
    
    node->add_node("Pepe","Mesa");
    node->add_node("Andres","Mesa");
    node->add_edge("Pepe","Andres","int","11");
    node->add_edge("Andres","Pepe","int","22");
    node->add_edge("Pepe","Andres","int","33");
    node->add_edge("Andres","Pepe","int","44");
    node->add_edge("Pepe","Andres","int","55");
    node->print_graph();
    int numero=node->get_edge_int("Pepe","Andres");

    RCLCPP_INFO(node->get_logger(), std::to_string(numero));

    //rclcpp::spin(node_neck);
    //auto node_neck = std::make_shared<NeckController>();
    //rclcpp::spin(node_neck);
    rclcpp::shutdown();
    return 0;
}