#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include "helpers.h"

int dfs(int i, int node, std::vector<bool> &visited, std::vector<int> &visitedNodes, networks::Graph &graph);
std::vector<int> topsort(networks::Graph &graph);

int main()
{   
#ifndef FILE_INPUT
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int numNodes, numEdges;
    std::cin >> numNodes >> numEdges;

    bool directed, weighted;
    std::cin >> directed >> weighted;

    std::vector<networks::Edge> edges;
    if (weighted)
    {
        for (int i=0; i<numEdges; i++)
        {
            int u, v, w;
            std::cin >> u >> v >> w;
            edges.push_back(networks::Edge(u, v, w));
        }
    }
    else
    {
        for (int i=0; i<numEdges; i++)
            {
                int u, v;
                std::cin >> u >> v;
                edges.push_back(networks::Edge(u, v));
            }
    }
    
    networks::Graph graph = networks::Graph(numNodes, edges, directed);
    std::vector<int> ordering;

    ordering = topsort(graph);
    helpers::printVector(ordering);

    return 0;
}


std::vector<int> topsort(networks::Graph &graph)
{
    int n = graph.numNodes;
    std::vector<bool> visited(n, false);
    std::vector<int> ordering(n);
    int i= n-1;

    for (int node=0; node<n; node++)
    {
        if (!visited[node])
            i = dfs(i, node, visited, ordering, graph);
        
    }

    return ordering;    
}

int dfs(int i, int node, std::vector<bool> &visited, std::vector<int> &ordering, networks::Graph &graph)
{
    visited[node] = true;

    std::vector<std::pair<int, int>> edges = graph.adjList[node];
    for (auto edge : edges)
    {
        if (!visited[edge.first])
            i = dfs(i, edge.first, visited, ordering, graph);
    }

    ordering[i] = node;
    return i-1;
}