#pragma once 

#include <vector> 
#include <string> 
#include <map> 
#include <cmath> 
#include <queue> 

/**
* MazeSolverSubsystem
* Implementation of the A* pathfinding algorithm 
* Solves a maze by finding the shortest path from (0,0) coordinate to goal 
*/
class MazeSolverSubsystem{ 
public: 
    /**
    * Constructor 
    * @param maze_data Serialized maze string in format: width,height|row1|row2..
    */
    MazeSolverSubsystem(const std::string& maze_data); 

    /**
    * Solve maze using A* algorithm 
    * @return True if sol found, else False 
    */
    bool solveMaze(); 

    /**
    * Get solution path coordinates 
    * @return String of coordinates 
    */
    std::string getSolutionPath() const; 

    /**
    * Get number of nodes explored by the algorithm 
    */
    int getNodesExplored() const; 

    /**
    * Get number of steps till solution 
    */
    int getPathLength() const; 

private: 
    //Maze data 
    std::vector<std::vector<bool>> m_maze; 
    int m_width; 
    int m_height; 

    //Solution data
    std::vector<std::pair<int, int>> m_solution_path; 
    int m_nodes_explored; 

    //Helper function 
    void parseMazeData(const std::string& maze_data);
    bool isValid(int x, int y) const;
    double heuristic(int x, int y) const;
}; 