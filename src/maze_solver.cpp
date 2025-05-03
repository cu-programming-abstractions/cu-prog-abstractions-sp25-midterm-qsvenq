#include "maze_solver.h"
#include <stack>
using namespace std;

bool MazeSolver::dfs(Maze& maze, int r, int c, vector<vector<bool>>& visited) {
    /* TODO: Implement recursive DFS with backtracking.

    Suggested steps:
    1. Guard   – out of bounds, wall, or already visited ➔ return false
    2. Goal    – if (r,c) == finish, add to path and return true
    3. Mark    – visited[r][c] = true
    4. Explore – recursively call dfs on N,E,S,W
    5. Success – if any recursive call returns true, push current cell onto
                 maze.path and return true
    6. Fail    – otherwise return false
    */

    // TODO: Your implementation here
    // 1. Guard – out of bounds, wall, or already visited ➔ return false
    if ((!maze.inBounds(r, c)) || (maze.isWall(r, c)) || (visited[r][c] == true))
    {
        return false;
    }

    // 2. Goal – if (r,c) == finish, return true
    if ((maze.finish.row == r) && (maze.finish.col == c))
    {
        return true;
    }

    // 3. Mark – visited[r][c] = true
    visited[r][c] = true;

    // 4. Explore – recursively call dfs on N,E,S,W

    // Create stack
    stack<Cell> toBeVisited;
    // Add neighbor cells
    toBeVisited.push({r + 1, c});
    toBeVisited.push({r - 1, c});
    toBeVisited.push({r, c + 1});
    toBeVisited.push({r, c - 1});

    while (!toBeVisited.empty())
    {
        // 5. Success – if any recursive call returns true, push current cell onto maze.path and return true
        if (dfs(maze, toBeVisited.top().row, toBeVisited.top().col, visited))
        {
            maze.path.push_back(toBeVisited.top());
            return true;
        }
        // pop the cell and try another route
        toBeVisited.pop();
    }

    // 6. Fail – otherwise return false
    return false;
}

bool MazeSolver::solveDFS(Maze& maze) {
    // Clear any existing path
    maze.path.clear();
    
    // Create visited matrix
    vector<vector<bool>> visited(maze.grid.size(), 
                               vector<bool>(maze.grid[0].size(), false));
    
    // Start DFS from the start position
    bool found = dfs(maze, maze.start.row, maze.start.col, visited);
    
    // If path found, add the start position to the path
    if (found) {
        maze.path.push_back(maze.start);
    }
    
    return found;
}
