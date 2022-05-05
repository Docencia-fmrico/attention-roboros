#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"

#include "ros2_knowledge_graph/GraphNode.hpp"
#include "gazebo_msgs/msg/model_state.hpp"

class GazeboGraph : public rclcpp::Node
{

    public:
        GazeboGraph() : Node("gazebo_graph") {
            graph_ = std::make_shared<ros2_knowledge_graph::GraphNode>("gazebo_graph");
            //graph_->start();
            subscription_gazebo_ = this->create_subscription<gazebo_msgs::msg::ModelState>(
            "/gazebo/model_states", 10, std::bind(&GazeboGraph::callback, this, std::placeholders::_1));
        }

    
    private:
        std::shared_ptr<ros2_knowledge_graph::GraphNode> graph_;
        rclcpp::Subscription<gazebo_msgs::msg::ModelState>::SharedPtr subscription_gazebo_;


        void callback(const gazebo_msgs::msg::ModelState::SharedPtr msg) const
        {
            RCLCPP_INFO(get_logger(),"callback");
        }
};