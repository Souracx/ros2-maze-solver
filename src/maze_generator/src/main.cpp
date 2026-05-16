#include "rclcpp/rclcpp.hpp"
#include "maze_generator/MazeGeneratorNode.hpp"

int main(int argc, char * argv[])
{
  // Initialize ROS2
  rclcpp::init(argc, argv);

  // Create and spin the node
  auto node = std::make_shared<MazeGeneratorNode>();
  rclcpp::spin(node);

  // Shutdown ROS2
  rclcpp::shutdown();

  return 0;
}