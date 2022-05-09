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

#include <vector>
#include <math.h>
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
#include "tf2_ros/buffer.h"
#include <tf2_ros/transform_listener.h>
#include "gazebo_msgs/msg/model_states.hpp"
#include <opencv2/opencv.hpp>

using namespace std::chrono_literals;
using std::placeholders::_1;

class NeckController : public rclcpp::Node
{
public:
  std::vector<std::string> names_objects;
  std::vector<geometry_msgs::msg::Pose> pose_objects;
  std::vector<int> want_see;
  NeckController() : rclcpp::Node("neck_controller")
  {
    publisher_ = create_publisher<trajectory_msgs::msg::JointTrajectory>(
      "/head_controller/joint_trajectory", 10);
    //graph_ = std::make_shared<ros2_knowledge_graph::GraphNode>("neck_controller");
    //graph_->start();  
    subscription_ = this->create_subscription<gazebo_msgs::msg::ModelStates>(
      "/gazebo/model_states", 10, std::bind(&NeckController::topic_callback, this, _1));
  }

  void doWork()
  {
    geometry_msgs::msg::Pose robot_pose;
    geometry_msgs::msg::Pose obj_pose;

    int dist = 0;
    get_object("tiago", names_objects, want_see);    
    if (want_see.empty()){
      std::cout << "no tiago";
      return;
    } 
    robot_pose = pose_objects[want_see[0]];

    get_object("cafe_table", names_objects, want_see);
    if (want_see.empty()){
      std::cout << "no_obj" << std::endl;
      return;
    }         
    obj_pose = pose_objects[want_see[0]];
    // std::cout << names_objects[want_see[0]] << std::endl;
    RCLCPP_INFO(get_logger(), "robot_x: %f, robot_y: %f, obj_x: %f, obj_y: %f", robot_pose.position.x, robot_pose.position.y, obj_pose.position.x, obj_pose.position.y);

    dist = sqrt( pow(robot_pose.position.x-obj_pose.position.x,2) + pow(robot_pose.position.y-obj_pose.position.y,2));
    
    std::cout << "dist:" <<dist << std::endl;
    if (dist > 5){
      return;
    }

  cv::Mat robot_mat(3,3, CV_32F, cv::Scalar(0));

  tf2::Quaternion q(
    robot_pose.orientation.x,
    robot_pose.orientation.y,
    robot_pose.orientation.z,
    robot_pose.orientation.w
  );
  tf2::Matrix3x3 m(q);
  double roll, pitch, yaw;
  m.getRPY(roll, pitch, yaw);
   // yaw -= 30;
  robot_mat.at<float>(0,0) = cos(yaw);
  robot_mat.at<float>(0,1) = -sin(yaw);
  robot_mat.at<float>(0,2) = robot_pose.position.x;
  robot_mat.at<float>(1,0) = sin(yaw);
  robot_mat.at<float>(1,1) = cos(yaw);
  robot_mat.at<float>(1,2) = robot_pose.position.y;
  robot_mat.at<float>(2,0) = 0;
  robot_mat.at<float>(2,1) = 0;
  robot_mat.at<float>(2,2) = 1;

  cv::Mat object_mat(3,1, CV_32F, cv::Scalar(0));
  
  object_mat.at<float>(0,0) = obj_pose.position.x;
  object_mat.at<float>(1,0) = obj_pose.position.y;
  object_mat.at<float>(2,0) = 1.0;

  object_mat = robot_mat * object_mat;
  if (object_mat.at<float>(1,0) < 0){
    std::cout << "Behind Tiago" << object_mat.at<float>(1,0) << std::endl;

  } else {
    std::cout << "In front" << std::endl;
      trajectory_msgs::msg::JointTrajectory message;
      message.header.frame_id = "base_link";
      message.header.stamp = now();
      message.joint_names = {"head_1_joint", "head_2_joint"};
      message.points.resize(1);
      message.points[0].positions.resize(2);
      message.points[0].accelerations.resize(2);
      message.points[0].velocities.resize(2);
      message.points[0].positions[0] = atan2(object_mat.at<float>(0,0),object_mat.at<float>(1,0)) + 0.9;
      std::cout << atan2(object_mat.at<float>(0,0),object_mat.at<float>(1,0)) << std::endl;
      message.points[0].positions[1] = 0.0;
      message.points[0].velocities[0] = 0.1;
      message.points[0].velocities[1] = 0.1;
      message.points[0].accelerations[0] = 0.1;
      message.points[0].accelerations[1] = 0.1;
      message.points[0].time_from_start = rclcpp::Duration(5s);
      RCLCPP_INFO(get_logger(), "Publishing [.]" );
      publisher_->publish(message);        
    }
      
  }

private:
    void topic_callback(const gazebo_msgs::msg::ModelStates::SharedPtr msg)
    {
        // Clear vectors 
        names_objects.clear();
        pose_objects.clear();
       // Copying vector by copy function
      copy(msg->name.begin(), msg->name.end(), back_inserter(names_objects));
      copy(msg->pose.begin(), msg->pose.end(), back_inserter(pose_objects));
      //names_objects.assign(msg->name.begin(), msg->name.end());
      // get_object("tiago", names_objects, want_see);

      // for (int i = 0; i < want_see.size(); i++) {
      // RCLCPP_INFO(this->get_logger(), "I heard %s", msg->name[want_see[i]].c_str());
      // }
      // if (is_in_list) {
      //   RCLCPP_INFO(this->get_logger(), "I heard: yes it is");
      // } else {
      //   RCLCPP_INFO(this->get_logger(), "I heard: no it dont work");
      // }
      /*
      for (int i = 0; i < msg->pose.size(); i++) {
        RCLCPP_INFO(this->get_logger(),"%f,%f,%f - %f,%f,%f,%f\n", pose_objects[i].position.x, pose_objects[i].position.y, pose_objects[i].position.z, pose_objects[i].orientation.x, pose_objects[i].orientation.y, pose_objects[i].orientation.z, pose_objects[i].orientation.w);
      }
      */
    }

    void get_object(std::string name_to_find, std::vector<std::string> names_ob, std::vector<int> &want_see_pos)
    {
      want_see_pos.clear();
      // Retorna vector con posiciones del vector original del objeto a ver      

      int found;
      for (int i = 0; i < names_ob.size(); i++) {
        found = names_ob[i].find(name_to_find);
        //RCLCPP_INFO(this->get_logger(), "I heard %d", found);
        if (found != std::string::npos) {
          want_see_pos.push_back(i);
        }
      }
    }

    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr publisher_;
    rclcpp::Subscription<gazebo_msgs::msg::ModelStates>::SharedPtr subscription_;
    //std::shared_ptr<ros2_knowledge_graph::GraphNode> graph_;        
    std::shared_ptr<tf2_ros::TransformListener> transform_listener_{nullptr};
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;    
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