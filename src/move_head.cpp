// Copyright 2020 Intelligent Robotics Lab
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

using namespace std::chrono_literals;



int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("simple_node_pub");
  auto publisher = node->create_publisher<trajectory_msgs::msg::JointTrajectory>(
    "/head_controller/joint_trajectory", 10);
  
  int counter = 0;
  rclcpp::Rate loop_rate(500ms);
  trajectory_msgs::msg::JointTrajectory message;
  /*
  message.header.frame_id = "head_1_link";
  message.header.stamp = now();
  message.joint_names = {"head_1_joint", "head_2_joint"};
  
  trajectory_msgs::msg::JointTrajectoryPoint points;
  points.positions = {(float)1.0, (float)1.5};
  points.velocities = {(float)0.1, (float)0.1};
  points.accelerations = {(float)0.1, (float)0.1};
  // points.effort = {(float)0.1, (float)0.1};
  points.time_from_start = rclcpp::Duration(1s);
  message.points = {points};
  */
  message.header.frame_id = "base_link";
  std_msgs::msg::Float64 m;
  message.header.stamp = node->now();
  message.joint_names = {"head_1_joint", "head_2_joint"};
  message.points.resize(2);
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

  message.points[1].positions.resize(2);
  message.points[1].accelerations.resize(2);
  message.points[1].velocities.resize(2);
  message.points[1].positions[0] = 1.3;
  message.points[1].positions[1] = 0.2;
  message.points[1].velocities[0] = 1.0;
  message.points[1].velocities[1] = 1.0;
  message.points[1].accelerations[0] = 1.1;
  message.points[1].accelerations[1] = 1.1;
  message.points[1].time_from_start = rclcpp::Duration(5s);

  while (rclcpp::ok()) {
    
    RCLCPP_INFO(node->get_logger(), "Publishing []" );

    publisher->publish(message);

    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
    
  rclcpp::shutdown();

  return 0;
}