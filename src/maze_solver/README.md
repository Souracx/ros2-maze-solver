# maze_solver - ROS2 Maze Solver Service 

ROS2 package that solves mazes using the A* pathfinding algorithm.

## Package Overview - MazeSoverPackage

This package provides a service client that requests a maze from `maze_generator` service, solves it using a A* pathfinding algorithm and publishes solution metric to topic. 

## Components 

1. **MazeSolverSubsystem** - A* pathfinding algorithm 
2. **MazeSolverNode** - ROS2 wrapper (service client + publisher)
3. **main.cpp** - Entry point

## How A* works? 

1. Start at (0,0), add it to open set 
2. Pick node with lowest f_cost = g_cost + h_cost 
3. If goal reached, reconstruct path and return
4. Otherwise, check 4 neighbors (up, down, left, right)
5. Update costs and add to open set
6. Repeat until goal found or open set empty

We use Manhattan distance as heuristic 

## Building
 
```bash
cd ~/art_mini_project
colcon build --packages-select maze_solver
```

## Running

### Prerequisites

`maze_generator` service must be running in another terminal:
```bash
ros2 run maze_generator maze_generator_node
```

### Run this package 

```bash
ros2 run maze_solver maze_solver_node
```
