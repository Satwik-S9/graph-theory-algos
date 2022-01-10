#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

int row, column;
int dr[4] = {-1, +1, 0, 0};
int dc[4] = {0, 0, +1, -1};
std::queue<int> rq;
std::queue<int> cq;
bool reached_end = false;
int move_count = 0;
int nodes_left_in_layer = 1;
int nodes_in_next_layer = 0;


void explore_neighbours(int r, int c, std::vector<std::vector<bool>> &visited, std::vector<std::vector<char>> &m)
{
    for (int i=0; i<4; i++)
    {
        int rr = r+dr[i];
        int cc = c+dc[i];

        // # skip out of bounds locations
        if (rr < 0 || cc < 0) continue;
        if (rr >= row or cc >= column) continue;

        // # skip visited locations or blocked cells
        if (visited[rr][cc]) continue;
        if (m[rr][cc] == '#') continue;

        rq.push(rr);
        cq.push(cc);
        visited[rr][cc] = true;
        nodes_in_next_layer++;
    }
}

int solve(int sr, int sc, std::vector<std::vector<bool>> &visited, std::vector<std::vector<char>> &m)
{
    rq.push(sr);
    cq.push(sc);
    visited[sr][sc] = true;

    while (!rq.empty())
    {
        int r = rq.front(); rq.pop();
        int c = cq.front(); cq.pop();

        if (m[r][c] == 'E')
        {
            reached_end = true;
            break;
        }
        explore_neighbours(r, c, visited, m);
        nodes_left_in_layer--;
        if (nodes_left_in_layer == 0)
        {
            nodes_left_in_layer = nodes_in_next_layer;
            nodes_in_next_layer = 0;
            move_count++;
        }    
    }

    if (reached_end)
        return move_count;

    return -1;
}

int main()
{
#ifndef FILE_INPUT
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    std::cin >> row >> column;

    // int m[row][column];
    char temp;
    std::vector<std::vector<char>> m(row, std::vector<char>(column));
    for (int i=0; i<row; i++)
        for(int j=0; j<column; j++)
        {
            std::cin >> temp;
            m[i][j] = temp;
        }   

    int sr, sc;
    std::cin >> sr >> sc;
    
    std::vector<std::vector<bool>> visited(row, std::vector<bool>(column, false));

    int ans = solve(sr, sc, visited, m);
    std::cout << ans;
}


/*
""" 
You are trapped in a 2D Dungeon and need to find the quickest way out The dungeon is composed of unit cubes which 
may or may not be filled with rock. It takes one minute to move one unit north, south, east, west. You can't move
diagonally and maze is surrounded by solid rock on all sides.

* Is Escape possible ? If yes, how long will it take ?

The dungeon has a size of R * C and you start at S and theres an exit E. A cell full of rock is denoted by '#' and empty 
cells are represented by '.'      

* INPUT: 
R = 5, C = 7

. . . # . . .
. # . . . # .
. # . . . . .
. . # # . . .
# . # E . # . 

"""
*/