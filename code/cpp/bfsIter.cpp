#include <map>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include "helpers.h"

#include <iostream>


void bfs(networks::Graph &graph, std::vector<bool> &visited, int v, bool suppress=true)
{
    std::queue<int> que;
    que.push(v);
    visited[v] = true;

    while(!que.empty())
    {
        int node = que.front();
        que.pop();
        std::cout << node << " ";

        for (std::pair<int, int> u : graph.adjList[node])
        {
            if (!visited[u.first])
            {
                que.push(u.first);
                visited[u.first] = true;
            }
        }

    }
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
    std::vector<bool> visited2(numNodes, false);

    bfs(graph, visited1, 0);
}