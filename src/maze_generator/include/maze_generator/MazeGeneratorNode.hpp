#pragma once

#include "rclcpp/rclcpp.hpp"
#include "maze_generator/MazeGeneratorSubsystem.hpp"
#include "maze_generator/srv/generate_maze.hpp"
#include <memory>

/**
 * MazeGeneratorNode
 * 
 * ROS2 Node that provides a service to generate random mazes.
 * Inherits from rclcpp::Node 
 * 
 * Node: 
 * - Provides a service "generate_maze" that clients can call
 * - Uses MazeGeneratorSubsystem to generate the actual maze
 * - Returns maze data to the client via service response
 */
class MazeGeneratorNode : public rclcpp::Node {
public:
  /**
   * Constructor
   * Initializes the node, declares parameters, and sets up the service server
   */
  MazeGeneratorNode();

private:
  //Subsystem for maze generation 
  std::unique_ptr<MazeGeneratorSubsystem> m_mazeSubsystem;

  //ROS2 parameters
  int m_mazeWidth;
  int m_mazeHeight;
  double m_wallProbability;

  //Service server
  rclcpp::Service<maze_generator::srv::GenerateMaze>::SharedPtr m_generateMazeService;

  /**
   * Declares and retrieves ROS2 parameters
   */
  void declareAndGetParameters();

  /**
   * Callback for the generate_maze service
   * Called when a client requests a new maze
  */
  void generateMazeCallback(
    const std::shared_ptr<maze_generator::srv::GenerateMaze::Request> request,
    std::shared_ptr<maze_generator::srv::GenerateMaze::Response> response);
};