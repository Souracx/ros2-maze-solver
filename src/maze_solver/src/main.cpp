#include <rclcpp/rclcpp.hpp>
#include "maze_solver/MazeSolverNode.hpp"

/**
 * Main entry point for maze_solver_node
 */
int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  
  // Create the node
  auto node = std::make_shared<MazeSolverNode>();
  
  // Spin (run) the node
  rclcpp::spin(node);
  
  // Shutdown
  rclcpp::shutdown();
  
  return 0;
}