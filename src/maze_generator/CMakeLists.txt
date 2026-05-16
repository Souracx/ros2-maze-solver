cmake_minimum_required(VERSION 3.8)
project(maze_generator)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/GenerateMaze.srv"
  DEPENDENCIES std_msgs
  )

add_executable(maze_generator_node src/main.cpp src/MazeGeneratorNode.cpp src/MazeGeneratorSubsystem.cpp)

target_include_directories(maze_generator_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(maze_generator_node rclcpp std_msgs)

rosidl_target_interfaces(maze_generator_node
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

install(TARGETS maze_generator_node DESTINATION lib/${PROJECT_NAME})

ament_package()
