#include <map>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include "helpers.h"

#include <iostream>


std::vector<int> bfs(networks::Graph &graph, std::vector<bool> &visited, int v, bool suppress=true);
std::vector<int> reconstructPath(int, int, std::vector<int>);

//* function to find the shortest path 
std::vector<int> shortestPath(networks::Graph &graph, int start, int end)
{
    std::vector<bool> visited(graph.adjList.size(), false);
    std::vector<int> parents = bfs(graph, visited, start);

    return reconstructPath(start, end, parents);
}


int main()
{
#ifndef FILE_INPUT
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int numNodes, numEdges;
    std::cin >> numNodes >> numEdges;

    bool directed, weighted;
    std::cin >> weighted >> directed;

    int u, v, w;
    std::vector<networks::Edge> edges;
    if (weighted)
    {
        for (int i=0; i<numEdges; i++)
        {
            std::cin >> u >> v >> w;
            edges.push_back(networks::Edge(u, v, w));
        }
    }
    else
    {
        for (int i=0; i<numEdges; i++)
        {
            std::cin >> u >> v;
            edges.push_back(networks::Edge(u, v));
        }
    }

    // Initializing Graph and visited array
    networks::Graph graph = networks::Graph(numNodes, edges, directed);
    std::vector<bool> visited1(numNodes, false);

    std::vector<int> parents;
    parents = bfs(graph, visited1, 0, false);
    // helpers::printVector(parents);

    std::vector<int> path;
    path = shortestPath(graph, 0, 3);
    std::cout << "\nShortest Path to " << 3 << ":";
    helpers::printVector(path);

}


std::vector<int> bfs(networks::Graph &graph, std::vector<bool> &visited, int v, bool suppress)
{
    std::queue<int> que;
    que.push(v);
    visited[v] = true;
    std::vector<int> parents(graph.adjList.size(), -1);

    if (!suppress)
        std::cout << "Order of Traversal ";

    while(!que.empty())
    {
        int node = que.front();
        que.pop();

        if (!suppress)
            std::cout << node << " ";

        for (std::pair<int, int> u : graph.adjList[node])
        {
            if (!visited[u.first])
            {
                que.push(u.first);
                visited[u.first] = true;
                parents[u.first] = node;
            }
        }
    }

    return parents;
}

std::vector<int> reconstructPath(int start, int end, std::vector<int> parents)
{
    // reconstruct path going backwards from end
    std::vector<int> path;
    for (int i=end; i != -1; i=parents[i])
        path.push_back(i);
    
    std::reverse(path.begin(), path.end());

    // if start and end are connected return the path else return empty vector
    if (path[0] == start)
        return path;
    
    return {-1};
}