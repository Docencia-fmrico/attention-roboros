#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"

#include "ros2_knowledge_graph/GraphNode.hpp"

class GazeboGraph : public rclcpp::Node
{

    public:
        GazeboGraph() : Node("gazebo_graph") {
            graph_ = std::make_shared<ros2_knowledge_graph::GraphNode>("node_A");
            graph_->start();
        }

    
    private:
        std::shared_ptr<ros2_knowledge_graph::GraphNode> graph_;
};