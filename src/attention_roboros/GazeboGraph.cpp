#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"
#include "rclcpp/rclcpp.hpp"

#include "ros2_knowledge_graph_msgs/msg/graph.hpp"
#include "ros2_knowledge_graph_msgs/msg/graph_update.hpp"
#include "ros2_knowledge_graph_msgs/msg/node.hpp"
#include "ros2_knowledge_graph_msgs/msg/edge.hpp"

#include "ros2_knowledge_graph/graph_utils.hpp"
#include "ros2_knowledge_graph/GraphNode.hpp"


class GazeboGraph : public rclcpp::Node
{

    public:
        GazeboGraph() : Node("gazebo_graph") {

            //subscription_gazebo_ = this->create_subscription<gazebo_msgs::msg::ModelState>(
            //"/gazebo/model_states", 10, std::bind(&GazeboGraph::callback, this, std::placeholders::_1));
        }

        void GazeboGraph::add_node(std::string & name,std::string % type){
            if (command.size() == 2) {
                auto node = ros2_knowledge_graph::new_node(name, type);
                graph_->update_node(node);
            } else {
                RCLCPP_INFO(get_logger(),"Usage:add node [name] [type] ");
            }
        }

        void GazeboGraph::add_edge(std::string  & source,std::string & target,std::string & target.std::string & type,std::string & target)
        {          

            auto edge = ros2_knowledge_graph::get_edge(source, target, type, data);

            if (edge.has_value()) {
                graph_->update_edge(edge.value());
            } else {
                RCLCPP_INFO(get_logger(),"Could not add the edge ");
            }
        }

        void GazeboGraph::remove_node(std::string  & source)
        {          
            if (!graph_->remove_node(source)) {
                RCLCPP_INFO(get_logger(),"Could not remove the node");
            }
        }

    
    private:
        std::shared_ptr<ros2_knowledge_graph::GraphNode> graph_;
        //rclcpp::Subscription<gazebo_msgs::msg::ModelState>::SharedPtr subscription_gazebo_;


        /*void callback(const gazebo_msgs::msg::ModelState::SharedPtr msg) const
        {
            RCLCPP_INFO(get_logger(),"callback");
        }*/
};