cmake_minimum_required(VERSION 3.5)
project(attention_roboros)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(plansys2_msgs REQUIRED)
find_package(plansys2_executor REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(ros2_knowledge_graph REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(dependencies
    rclcpp
    rclcpp_action
    plansys2_msgs
    plansys2_executor
    trajectory_msgs
    std_msgs
    ros2_knowledge_graph
)

add_executable(move_head src/move_head.cpp)
ament_target_dependencies(move_head ${dependencies})

add_executable(attention_main src/attention_main.cpp)
ament_target_dependencies(attention_main ${dependencies})

add_executable(gazebo_graph src/attention_roboros/GazeboGraph.cpp)
ament_target_dependencies(gazebo_graph ${dependencies})

add_executable(neck_controller src/attention_roboros/NeckController.cpp)
ament_target_dependencies(neck_controller ${dependencies})



#install(DIRECTORY launch pddl DESTINATION share/${PROJECT_NAME})
install(DIRECTORY DESTINATION share/${PROJECT_NAME})

install(TARGETS
move_head
attention_main
gazebo_graph
neck_controller
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
endif()

ament_export_dependencies(${dependencies})

ament_package()