cmake_minimum_required(VERSION 3.8)
project(maze_solver)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(maze_generator REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/MazeSolution.msg"
  DEPENDENCIES std_msgs
)

# Add executable
add_executable(maze_solver_node 
  src/main.cpp 
  src/MazeSolverNode.cpp 
  src/MazeSolverSubsystem.cpp
)

# Include directories
target_include_directories(maze_solver_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Link dependencies
ament_target_dependencies(maze_solver_node rclcpp std_msgs maze_generator)

# Link the custom message
rosidl_target_interfaces(maze_solver_node
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

# Install the executable
install(TARGETS maze_solver_node DESTINATION lib/${PROJECT_NAME})

ament_package()