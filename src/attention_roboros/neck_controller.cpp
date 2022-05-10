// Copyright 2022 Roboros
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"

#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"
#include "ros2_knowledge_graph_msgs/msg/graph.hpp"
#include "ros2_knowledge_graph_msgs/msg/graph_update.hpp"
#include "ros2_knowledge_graph_msgs/msg/node.hpp"
#include "ros2_knowledge_graph_msgs/msg/edge.hpp"

#include "ros2_knowledge_graph/graph_utils.hpp"
#include "ros2_knowledge_graph/GraphNode.hpp"

using namespace std::chrono_literals;

class NeckController : public rclcpp::Node
{
public:
    NeckController() : rclcpp::Node("neck_controller") {
        auto publisher_ = create_publisher<trajectory_msgs::msg::JointTrajectory>(
        "/head_controller/joint_trajectory", 10);   
    }

    void doWork()
    {
        trajectory_msgs::msg::JointTrajectory message;
        message.header.frame_id = "base_link";
        message.header.stamp = now();
        message.joint_names = {"head_1_joint", "head_2_joint"};
        message.points.resize(1);
        message.points[0].positions.resize(2);
        message.points[0].accelerations.resize(2);
        message.points[0].velocities.resize(2);
        message.points[0].positions[0] = 0.3;
        message.points[0].positions[1] = 1.0;
        message.points[0].velocities[0] = 0.1;
        message.points[0].velocities[1] = 0.1;
        message.points[0].accelerations[0] = 0.1;
        message.points[0].accelerations[1] = 0.1;
        message.points[0].time_from_start = rclcpp::Duration(1s);
        RCLCPP_INFO(get_logger(), "Publishing []" );

        //RCLCPP_INFO(get_logger(), "Publishing [%s]", message.data.c_str());
        publisher_->publish(message);        
    }

private:
    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr publisher_;  
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);

    auto node = std::make_shared<NeckController>();
    rclcpp::Rate loop_rate(500ms);
    while(rclcpp::ok()){
        node->doWork();
        rclcpp::spin_some(node);
        loop_rate.sleep();

    }
    rclcpp::shutdown();

    return 0;
}