# maze_generator - ROS2 Maze Generation Service 

A ROS2 service that generate a random maze using probabilistic wall placement 

## Package Overview - MazeGeneratorPackage

This package provides a ROS2 service server that clients can call to request randomly generated mazes. The service accepts parameter (width, height, wall probability) and returns a serialized maze along with its dimensions.

## Components 
1. **MazeGeneratorSubsystem** - Maze generation logic 
2. **MazeGeneratorNode** - ROS2 wrapper (service server + parameters)
3. **main.cpp** - Entry point

**Request:**
```
int32 width              # Maze width
int32 height             # Maze height
float64 wall_probability # Wall probability (0.0-1.0)
```
 
**Response:**
```
string maze_data  # Serialized maze: "width,height|row1|row2|..."
int32 width       # Actual width generated
int32 height      # Actual height generated
```


## Building
 
```bash
cd ~/art_mini_project
colcon build --packages-select maze_generator
```

## Running
 
```bash
ros2 run maze_generator maze_generator_node
```

 
