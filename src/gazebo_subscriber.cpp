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
#include "gazebo_msgs/msg/model_states.hpp"
#include <vector>

using namespace std::chrono_literals;
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    std::vector<std::string> names_objects;
    std::vector<geometry_msgs::msg::Pose> pose_objects;
    std::vector<int> want_see;
    MinimalSubscriber()
    : Node("get_gazebo")
    {
      subscription_ = this->create_subscription<gazebo_msgs::msg::ModelStates>(
      "/gazebo/model_states", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const gazebo_msgs::msg::ModelStates::SharedPtr msg)
    {
       // Copying vector by copy function
      copy(msg->name.begin(), msg->name.end(), back_inserter(names_objects));
      copy(msg->pose.begin(), msg->pose.end(), back_inserter(pose_objects));
      //names_objects.assign(msg->name.begin(), msg->name.end());
      get_object("table", names_objects, want_see);

      for (int i = 0; i < want_see.size(); i++) {
        RCLCPP_INFO(this->get_logger(), "I heard %s", msg->name[want_see[i]].c_str());
      }
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
    
    rclcpp::Subscription<gazebo_msgs::msg::ModelStates>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
  
}