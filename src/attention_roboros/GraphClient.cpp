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


#include "ros2_knowledge_graph/GraphNode.hpp"

class GraphClient : public rclcpp::Node
{

    public:
        GraphClient()  : Node("graph_client") {
            //auto node = rclcpp::Node::make_shared("simple");
            //graph_= std::make_shared<ros2_knowledge_graph::GraphNode>(node);
        }

        void crear_garfo(){
            graph_= std::make_shared<ros2_knowledge_graph::GraphNode>(shared_from_this());
        }

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


        //std::string source,std::string target,std::string
        void print_graph(){
            RCLCPP_INFO(this->get_logger(), "-----------NODES----------  \n");
            std::vector<ros2_knowledge_graph_msgs::msg::Node>nodes_vector =graph_->get_nodes();

            for(auto V : nodes_vector){

                RCLCPP_INFO(this->get_logger(), "%s-%s \n",(V.node_name).c_str(),(V.node_class).c_str());
            }

            RCLCPP_INFO(this->get_logger(), "-----------EDGES----------  \n");
            std::vector<ros2_knowledge_graph_msgs::msg::Edge> edges_vector=graph_->get_edges();
            
            for(auto V : edges_vector){
                int num = (ros2_knowledge_graph::get_content<int>(V.content)).value();

                RCLCPP_INFO(this->get_logger(), "%s-%s %d  \n",(V.source_node_id).c_str(),(V.target_node_id).c_str(),num );
            }
            
        }



    

    
    private:
        std::shared_ptr<ros2_knowledge_graph::GraphNode> graph_;
};