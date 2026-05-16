#include "maze_solver/MazeSolverNode.hpp"

/**
 * Constructor - Initialize the ROS2 node
 */
MazeSolverNode::MazeSolverNode() : Node("maze_solver_node") {
  
  RCLCPP_INFO(this->get_logger(), "Maze Solver Node initialized");
  
  // Create service client to call maze_generator service
  m_service_client = this->create_client<maze_generator::srv::GenerateMaze>("generate_maze");
  
  // Create publisher for solution metrics
  m_publisher = this->create_publisher<maze_solver::msg::MazeSolution>("maze_solver/solution_metrics", 10);
  
  RCLCPP_INFO(this->get_logger(), "Service client created for 'generate_maze'");
  RCLCPP_INFO(this->get_logger(), "Publisher created for 'maze_solver/solution_metrics'");
  
  // Create a timer that fires once after 1 second
  m_timer = this->create_wall_timer(
    std::chrono::seconds(1),
    std::bind(&MazeSolverNode::timerCallback, this)
  );
  
  RCLCPP_INFO(this->get_logger(), "Timer started - will request maze in 1 second");
}

/**
 * Timer callback - Request maze and solve it
 */
void MazeSolverNode::timerCallback() {
  // Cancel the timer so it only runs once
  m_timer->cancel();
  
  RCLCPP_INFO(this->get_logger(), "Requesting maze from service...");
  
  // Create request with desired maze parameters
  auto request = std::make_shared<maze_generator::srv::GenerateMaze::Request>();
  request->width = 20;
  request->height = 20;
  request->wall_probability = 0.3;
  
  // Call the service asynchronously with callback
  auto future = m_service_client->async_send_request(
    request,
    [this](rclcpp::Client<maze_generator::srv::GenerateMaze>::SharedFuture future) {
      auto response = future.get();
      
      RCLCPP_INFO(this->get_logger(), "Received maze (%d x %d)", response->width, response->height);
      
      // Create subsystem with maze data
      m_subsystem = std::make_unique<MazeSolverSubsystem>(response->maze_data);
      
      // Solve the maze
      RCLCPP_INFO(this->get_logger(), "Solving with A*...");
      bool solved = m_subsystem->solveMaze();
      
      if (solved) {
        RCLCPP_INFO(this->get_logger(), "Solution found!");
        publishMetrics();
      } else {
        RCLCPP_ERROR(this->get_logger(), "No solution found!");
      }
    }
  );
}

/**
 * Publish the solution metrics to the topic
 */
void MazeSolverNode::publishMetrics() {
  // Create the message
  auto message = maze_solver::msg::MazeSolution();
  
  // Fill in the metrics
  message.path_length = m_subsystem->getPathLength();
  message.nodes_explored = m_subsystem->getNodesExplored();
  message.solve_time_seconds = 0.0;  // TODO: Add actual timing later
  message.solution_path = m_subsystem->getSolutionPath();
  
  // Log the metrics to console
  RCLCPP_INFO(this->get_logger(), "Solution Path:");
  RCLCPP_INFO(this->get_logger(), "%s", message.solution_path.c_str());
  
  RCLCPP_INFO(this->get_logger(), "\nMetrics:");
  RCLCPP_INFO(this->get_logger(), "- Path length: %d steps", message.path_length);
  RCLCPP_INFO(this->get_logger(), "- Nodes explored: %d", message.nodes_explored);
  RCLCPP_INFO(this->get_logger(), "- Solve time: %f seconds", message.solve_time_seconds);
  
  // Publish the message
  m_publisher->publish(message);
  
  RCLCPP_INFO(this->get_logger(), "Metrics published to topic 'maze_solver/solution_metrics'");
}