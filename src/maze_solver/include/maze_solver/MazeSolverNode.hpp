#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "maze_solver/MazeSolverSubsystem.hpp"
#include "maze_generator/srv/generate_maze.hpp"
#include "maze_solver/msg/maze_solution.hpp"

/**
 * MazeSolverNode
 * 
 * ROS2 Node that acts as a service client.
 * Requests a maze from maze_generator service, solves it with A*, and publishes the solution metrics.
 */
class MazeSolverNode : public rclcpp::Node {
public:
  /**
   * Constructor
   */
  MazeSolverNode();

private:
  // Service client to call maze_generator
  rclcpp::Client<maze_generator::srv::GenerateMaze>::SharedPtr m_service_client;
  
  // Publisher for solution metrics
  rclcpp::Publisher<maze_solver::msg::MazeSolution>::SharedPtr m_publisher;
  
  // The maze solver subsystem
  std::unique_ptr<MazeSolverSubsystem> m_subsystem;
  
  // Timer to trigger maze solving
  rclcpp::TimerBase::SharedPtr m_timer;
  
  /**
   * Timer callback that requests maze and solves it
   */
  void timerCallback();
  
  /**
   * Publish the solution metrics to the topic
   */
  void publishMetrics();
};