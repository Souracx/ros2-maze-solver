#include "maze_generator/MazeGeneratorNode.hpp"

MazeGeneratorNode::MazeGeneratorNode() : Node("maze_generator_node") {
  // Declare and get parameters
  declareAndGetParameters();

  // Create the subsystem with parameters
  m_mazeSubsystem = std::make_unique<MazeGeneratorSubsystem>(m_mazeWidth, m_mazeHeight, m_wallProbability);

  // Create service server
  m_generateMazeService = this->create_service<maze_generator::srv::GenerateMaze>("generate_maze",
    std::bind(&MazeGeneratorNode::generateMazeCallback, this,
      std::placeholders::_1, std::placeholders::_2));

  RCLCPP_INFO(this->get_logger(), "Maze Generator Node initialized");
  RCLCPP_INFO(this->get_logger(), "Parameters: width=%d, height=%d, wall_probability=%.2f",m_mazeWidth, m_mazeHeight, m_wallProbability);
  RCLCPP_INFO(this->get_logger(), "Service 'generate_maze' is ready");
}

void MazeGeneratorNode::declareAndGetParameters() {
  // Declare parameters with default values
  this->declare_parameter("maze_width", 20);
  this->declare_parameter("maze_height", 20);
  this->declare_parameter("wall_probability", 0.3);

  // Get parameter values
  m_mazeWidth = this->get_parameter("maze_width").as_int();
  m_mazeHeight = this->get_parameter("maze_height").as_int();
  m_wallProbability = this->get_parameter("wall_probability").as_double();

  // Validate parameters
  if (m_mazeWidth < 1) m_mazeWidth = 1;
  if (m_mazeHeight < 1) m_mazeHeight = 1;
  if (m_wallProbability < 0.0) m_wallProbability = 0.0;
  if (m_wallProbability > 1.0) m_wallProbability = 1.0;
}

void MazeGeneratorNode::generateMazeCallback(
  const std::shared_ptr<maze_generator::srv::GenerateMaze::Request> request,
  std::shared_ptr<maze_generator::srv::GenerateMaze::Response> response) {
  
  RCLCPP_INFO(this->get_logger(), "Service request received: width=%d, height=%d, probability=%.2f",
              request->width, request->height, request->wall_probability);
  
  // Create subsystem with requested parameters
  MazeGeneratorSubsystem maze(request->width, request->height, request->wall_probability);
  maze.generateMaze();
  
  // Set response data
  response->maze_data = maze.getMazeString();
  response->width = maze.getWidth();
  response->height = maze.getHeight();
  
  RCLCPP_INFO(this->get_logger(), "Generated maze (%dx%d), sent response",
              response->width, response->height);
}