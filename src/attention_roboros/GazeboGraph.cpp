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


class GazeboGraph
{

    public:

        void add_node(std::string name,std::string type){

            auto node = ros2_knowledge_graph::new_node(name, type);
            graph_->update_node(node);

            std::cout << "Nodo añadido: " << name << "\n";

        }

        void add_edge(std::string source,std::string target,std::string type)
        {          

            auto edge = ros2_knowledge_graph::new_edge(source, target, type);

            graph_->update_edge(edge);
            std::cout << "Edge añadido entre " << source << "y" << target << "\n";

        }

        void remove_node(std::string source)
        {          
            if (!graph_->remove_node(source)) {
                std::cout << "No pudo remover edge: "<<source<< "\n";
            }
        }

    
    private:
        std::shared_ptr<ros2_knowledge_graph::GraphNode> graph_;
};