#pragma once

#include <vector>
#include <string>

/**
 * MazeGeneratorSubsystem
 * 
 * Generates random mazes with configurable dimensions and wall probability.
 * This subsystem contains pure C++ maze generation logic and does NOT depend on ROS2.
 * Uses probabilistic wall placement with guaranteed walkable start and goal areas.
 */
class MazeGeneratorSubsystem {
public:
  /**
   * Constructor
   * 
   * @param width Maze width in cells
   * @param height Maze height in cells
   * @param wallProbability Probability of placing a wall (0.0 to 1.0)
   */
  MazeGeneratorSubsystem(int width, int height, double wallProbability);

  /**
   * Generates a new random maze
   * Places walls probabilistically and ensures start (0,0) and goal areas remain walkable
   */
  void generateMaze();

  /**
   * Gets the generated maze as a serialized string
   * Format: "width,height|row1|row2|..." where 1=wall, 0=open
   * 
   * @return String representation of the maze
   */
  std::string getMazeString() const;

  /**
   * Gets the raw 2D maze data
   * 
   * @return Const reference to 2D vector where true=wall, false=open
   */
  const std::vector<std::vector<bool>>& getMazeData() const;

  /**
   * Gets maze width
   * 
   * @return Width in cells
   */
  int getWidth() const;

  /**
   * Gets maze height
   * 
   * @return Height in cells
   */
  int getHeight() const;

  /**
   * Checks if a specific cell is walkable (not a wall)
   * 
   * @param x X-coordinate
   * @param y Y-coordinate
   * @return True if cell is open, false if wall or out of bounds
   */
  bool isWalkable(int x, int y) const;

private:
  int m_width;
  int m_height;
  double m_wallProbability;
  std::vector<std::vector<bool>> m_maze;

  /**
   * Helper function to ensure start (0,0) and goal areas are walkable
   * Clears walls in a 3x3 area around start and goal positions
   */
  void ensureWalkableAreas();
};