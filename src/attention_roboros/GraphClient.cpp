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


class GraphClient
{

    public:

        void add_node(std::string name,std::string type){

            auto node = ros2_knowledge_graph::new_node(name, type);
            graph_->update_node(node);

            //std::cout << "Nodo añadido: " << name << "\n";

        }

        void add_edge(std::string source,std::string target,std::string type,std::string content)
        {          
            ros2_knowledge_graph_msgs::msg::Edge edge;

            if (type == "bool") {
                edge = ros2_knowledge_graph::new_edge<bool>(source, target, content == "true");
            } else if (type == "int") {
                edge = ros2_knowledge_graph::new_edge<int>(source, target, atoi(content.c_str()));
            } else if (type == "float") {
                edge = ros2_knowledge_graph::new_edge<float>(source, target, atof(content.c_str()));
            } else if (type == "double") {
                edge = ros2_knowledge_graph::new_edge<double>(source, target, atof(content.c_str()));
            } else if (type == "string") {
                edge = ros2_knowledge_graph::new_edge<std::string>(source, target, content);
            }

            graph_->update_edge(edge);
            //std::cout << "Edge añadido entre " << source << "y" << target << "\n";

        }

        void remove_node(std::string source)
        {          
            if (!graph_->remove_node(source)) {
                //std::cout << "No pudo remover node: "<<source<< "\n";
            }
        }

    

    
    private:
        std::shared_ptr<ros2_knowledge_graph::GraphNode> graph_;
};