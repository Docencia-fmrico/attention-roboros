#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"

#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"

class NeckController : public rclcpp::Node
{

    public:
        NeckController() : Node("neck_controller") {
            auto publisher_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>(
            "/head_controller/joint_trajectory", 10);
        }

        void doWork()
        {
            trajectory_msgs::msg::JointTrajectory message;
            message.header.frame_id = "base_link";
            message.header.stamp = node->now();
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

            RCLCPP_INFO(get_logger(), "Publishing [%s]", message.data.c_str());
            publisher_->publish(message);        
        }
    
    private:
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);

    auto node = std::make_shared<NeckController>();
    rlcpp::Rate loop_rate(500ms);
    while(rclcpp::ok()){
        node->doWork();
        rclcpp::spin_some(node);
        loop_rate.sleep();

    }
    rlcpp::shutdown();

    return 0;
}