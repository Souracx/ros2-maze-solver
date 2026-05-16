#include "maze_solver/MazeSolverSubsystem.hpp"

/**
* Constructor - Initialize subsystem 
*/
MazeSolverSubsystem::MazeSolverSubsystem(const std::string& maze_data) : m_width(0), m_height(0), m_nodes_explored(0) {
    parseMazeData(maze_data); 
}

/**
 * Parse the serialized maze string into 2D vector
 * Format: "width,height|row1|row2|..."
 * Where 1 = wall, 0 = open space
 */
void MazeSolverSubsystem::parseMazeData(const std::string& maze_data) {
  // Find separator between dimensions and maze data
  size_t pipe_position = maze_data.find('|');
  
  // Parse width and height
  size_t comma_position = maze_data.find(',');
  m_width = std::stoi(maze_data.substr(0, comma_position));
  m_height = std::stoi(maze_data.substr(comma_position + 1, pipe_position - comma_position - 1));

  // Clear any old maze data
  m_maze.clear();
  size_t current_position = pipe_position + 1;
  
  // Parse each row
  for (int row = 0; row < m_height; row++) {
    size_t next_pipe = maze_data.find('|', current_position);
    if (next_pipe == std::string::npos) {
      next_pipe = maze_data.length();
    }
    
    // Extract the row string
    std::string row_str = maze_data.substr(current_position, next_pipe - current_position);
    std::vector<bool> maze_row;
    
    // Convert each character to bool
    for (char c : row_str) {
      maze_row.push_back(c == '1');
    }
    // Add the row to the maze
    m_maze.push_back(maze_row);
    // Move to next row
    current_position = next_pipe + 1;
  }
}

/**
* Check if a position (x,y) is valid (within bounds)
*/
bool MazeSolverSubsystem::isValid(int x, int y) const{ 
    return x >= 0 && x < m_width && y >= 0 && y < m_height && !m_maze[y][x]; 
}  

/**
* Manhatan distance (heuristic function for A* algorithm )
* Lower value = closer to goal 
*/
double MazeSolverSubsystem::heuristic(int x, int y) const{ 
    int goalX = m_width - 1; 
    int goalY = m_height - 1; 
    return std::abs(x - goalX) + std::abs(y - goalY); 
}

/**
* Get solution path as string 
*/
std::string MazeSolverSubsystem::getSolutionPath() const{ 
    std::string res; 
    for(size_t i = 0; i < m_solution_path.size(); i++){
         res += "(" + std::to_string(m_solution_path[i].first) + "," + std::to_string(m_solution_path[i].second) + ")"; 
    
    if (i < m_solution_path.size() - 1){
        res += "->"; 
        }
    }
    return res; 
}

int MazeSolverSubsystem::getNodesExplored() const{
    return m_nodes_explored; 
}

int MazeSolverSubsystem::getPathLength() const{ 
    return m_solution_path.size(); 
}

/** 
* A* Algorithm 
*/
bool MazeSolverSubsystem::solveMaze() { 
    //Check if start is valid
    if (!isValid(0,0)){
        return false; 
    }
    int goalX = m_width - 1; 
    int goalY = m_height - 1; 

    //Check if valid goal 
    if (!isValid(goalX, goalY)){ 
        return false;
    }

    //Reset 
    m_solution_path.clear(); 
    m_nodes_explored = 0; 

    std::map<std::pair<int, int>, double> g_cost; 
    std::map<std::pair<int, int>, std::pair<int, int>> parent; 

    //priority queue - comperator 
    auto cmp = [](const std::tuple<double, int, int>& a, std::tuple<double, int, int>& b){ 
        return std::get<0>(a) > std::get<0>(b); 
    }; 
    std::priority_queue<std::tuple<double, int, int>,std::vector<std::tuple<double, int, int>>, decltype(cmp) > open_set(cmp); 

    //Initialize start and goal 
    std::pair<int, int> start = {0, 0}; 
    std::pair<int, int> goal = {goalX, goalY}; 

    g_cost[start] = 0.0; 
    double f_cost_start = heuristic(0,0); 
    open_set.push(std::make_tuple(f_cost_start, 0, 0)); 

    //A* main loop 
    while(!open_set.empty()){ 
        auto node = open_set.top(); 
        double f = std::get<0>(node); 
        int current_x = std::get<1>(node); 
        int current_y = std::get<2>(node); 
        open_set.pop(); 

        std::pair<int, int> current = {current_x, current_y}; 

        //count node as explored
        m_nodes_explored++; 

        //Goal reached 
        if(current == goal){ 
            //reconstruct path 
            std::pair<int, int> node = goal; 
            while(node != start){ 
                m_solution_path.insert(m_solution_path.begin(), node); 
                node = parent[node]; 
            }
            m_solution_path.insert(m_solution_path.begin(), node); 
            return true; 
        }
        //check all neighbours 
        int dx[] = {0, 0, 1, -1}; 
        int dy[] = {-1, 1, 0, 0}; 
        for (int i = 0; i < 4; i++){
            int next_x = current_x + dx[i]; 
            int next_y = current_y + dy[i]; 

            //skip if invalid
            if (!isValid(next_x, next_y)){ 
                continue; 
            }
            std::pair<int, int> neighbour = {next_x, next_y}; 

            //cost to move neighbour 
            double candidate_g_cost = g_cost[current] + 1.0; 
            //if better path found 
            if(g_cost.find(neighbour) == g_cost.end() || candidate_g_cost < g_cost[neighbour]){ 
                parent[neighbour] = current; 
                g_cost[neighbour] = candidate_g_cost; 

                double f = candidate_g_cost + heuristic(next_x, next_y); 
                open_set.push(std::make_tuple(f, next_x, next_y)); 
            }
        }
    }
    //No path found 
    return false; 
}

