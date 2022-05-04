#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"

#include "ros2_knowledge_graph/GraphNode.hpp"
#include "gazebo_msgs/msg/ModelStates"

class GazeboGraph : public rclcpp::Node
{

    public:
        GazeboGraph() : Node("gazebo_graph") {
            graph_ = std::make_shared<ros2_knowledge_graph::GraphNode>("node_A");
            graph_->start();
            subscription_gazebo_ = this->create_subscription<gazebo_msgs::msg::ModelStates>(
            "/gazebo/model_states", 10, std::bind(&GazeboGraph::callback, this, _1));
        }

    
    private:
        std::shared_ptr<ros2_knowledge_graph::GraphNode> graph_;
        rclcpp::Subscription<gazebo_msgs::msg::ModelStates>::SharedPtr subscription_gazebo_;


        void callback(const gazebo_msgs::msg::ModelStates::SharedPtr msg) const
        {
            RCLCPP_INFO("callback");
        }
};