#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>

#include "helpers.h"


std::vector<int> topsort(networks::Graph &graph);
std::pair<std::vector<int>, int> shortestPathDAG(networks::Graph &graph, int start, int target);
int dfs(int i, int node, std::vector<bool> &visited, std::vector<int> &visitedNodes, networks::Graph &graph);


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

    networks::Graph graph = networks::Graph(numNodes, edges, directed);

    int target = graph.numNodes-1;
    std::pair<std::vector<int>, int> ans = shortestPathDAG(graph, 0, target); 
    helpers::printVector(ans.first, "The Shortest path Array in the Given DAG is: ");
    std::cout << "The shortest path to " << target << " is " << ans.second;

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

std::pair<std::vector<int>, int> shortestPathDAG(networks::Graph &graph, int start, int target)
{
    if (target == -1) target = graph.numNodes-1;

    std::vector<int> ordering = topsort(graph);
    std::vector<int> distance(graph.numNodes, INT32_MAX);
    distance[start] = 0;

    for (int i=0; i < graph.numNodes; i++)
    {
        int nodeIndex = ordering[i];
        std::vector<std::pair<int, int>> adjEdges = graph.adjList[nodeIndex];
        for (auto edge : adjEdges)
        {
            int newDist = distance[nodeIndex] + edge.second;
            if (distance[edge.first] == INT32_MAX) distance[edge.first] = newDist;
            else distance[edge.first] = std::min(distance[edge.first], newDist);
        }
    }

    std::pair<std::vector<int>, int> ans = {distance, distance[target]};
    return ans;
}