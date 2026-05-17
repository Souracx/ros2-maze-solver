# ROS2 Maze Generator and Solver

A complete ROS2 system that generates random mazes and solves them using the A* pathfinding algorithm.

## Project Overview

**Architecture:**

**maze_generator:** Stateless service server implementing probabilistic Cellular Automata for maze generation. Exposes `GenerateMaze` service with configurable parameters (width, height, wall_probability).

**maze_solver:** Asynchronous service client implementing the A* pathfinding algorithm with Manhattan distance heuristic. Subscribers to service responses via callbacks, avoiding blocking operations on the ROS executor.


## How to start Quick Start
 
### Terminal 1: Start Maze Generator
 
```bash
cd ~/art_mini_project
source install/setup.bash
ros2 run maze_generator maze_generator_node
```

### Terminal 2: Start Maze Solver
 
```bash
cd ~/art_mini_project
source install/setup.bash
ros2 run maze_solver maze_solver_node
```



## Building
 
### Prerequisites
 
- Ubuntu 22.04 LTS
- ROS 2 Humble
- C++17 compiler
### Build Commands
 
```bash
# Navigate to workspace
cd ~/art_mini_project
 
# Source ROS2
source /opt/ros/humble/setup.bash
 
# Build all packages
colcon build
 
# Source the build
source install/setup.bash
```
