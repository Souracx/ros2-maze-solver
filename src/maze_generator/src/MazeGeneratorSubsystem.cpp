#include "maze_generator/MazeGeneratorSubsystem.hpp"
#include <random>
#include <sstream>
#include <algorithm>

MazeGeneratorSubsystem::MazeGeneratorSubsystem(int width, int height, double wallProbability): m_width(width), m_height(height),m_wallProbability(wallProbability) {
  // Validate and constrain parameters
  if (m_width < 1) m_width = 1;
  if (m_height < 1) m_height = 1;
  if (m_wallProbability < 0.0) m_wallProbability = 0.0;
  if (m_wallProbability > 1.0) m_wallProbability = 1.0;
}

void MazeGeneratorSubsystem::generateMaze() {
  // Initialize maze with all open spaces (false = no wall)
  m_maze.assign(m_height, std::vector<bool>(m_width, false));

  // Set up random number generator with random seed
  std::random_device rd;
  std::mt19937 generator(rd());

  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  // Generate walls based on probability
  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      double randomValue = distribution(generator);
      if (randomValue < m_wallProbability) {
        m_maze[y][x] = true;  // Place wall
      }
    }
  }

  // Ensure start and goal areas are walkable
  ensureWalkableAreas();
}

void MazeGeneratorSubsystem::ensureWalkableAreas() {
  // NOTE: Ensure start area (0,0) is walkable - clear 3x3 area around it
  int startXMin = std::max(0, 0 - 1);
  int startXMax = std::min(m_width - 1, 0 + 1);
  int startYMin = std::max(0, 0 - 1);
  int startYMax = std::min(m_height - 1, 0 + 1);

  for (int y = startYMin; y <= startYMax; ++y) {
    for (int x = startXMin; x <= startXMax; ++x) {
      m_maze[y][x] = false;
    }
  }

  // NOTE: Ensure goal area (bottom-right) is walkable - clear 3x3 area
  int goalX = m_width - 1;
  int goalY = m_height - 1;

  int goalXMin = std::max(0, goalX - 1);
  int goalXMax = std::min(m_width - 1, goalX + 1);
  int goalYMin = std::max(0, goalY - 1);
  int goalYMax = std::min(m_height - 1, goalY + 1);

  for (int y = goalYMin; y <= goalYMax; ++y) {
    for (int x = goalXMin; x <= goalXMax; ++x) {
      m_maze[y][x] = false;
    }
  }
}

std::string MazeGeneratorSubsystem::getMazeString() const {
  std::stringstream ss;

  // Store dimensions
  ss << m_width << "," << m_height << "|";

  // Serialize maze data - each row separated by |
  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      ss << (m_maze[y][x] ? '1' : '0');
    }
    ss << "|";
  }

  return ss.str();
}

const std::vector<std::vector<bool>>& MazeGeneratorSubsystem::getMazeData() const {
  return m_maze;
}

int MazeGeneratorSubsystem::getWidth() const {
  return m_width;
}

int MazeGeneratorSubsystem::getHeight() const {
  return m_height;
}

bool MazeGeneratorSubsystem::isWalkable(int x, int y) const {
  // Out of bounds is not walkable
  if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
    return false;
  }

  // Return true if NOT a wall
  return !m_maze[y][x];
}