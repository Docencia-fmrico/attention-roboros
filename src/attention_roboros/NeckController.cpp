#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"

#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"

class NeckController : public rclcpp::Node
{

    public:
        NeckController() : Node("gazebo_graph") {
            auto publisher_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>(
            "/head_controller/joint_trajectory", 10);
        }

    
    private:
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        
};