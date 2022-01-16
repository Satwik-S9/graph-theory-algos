#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "helpers.h"


void dfs(networks::Graph &graph, int node, std::vector<bool> &visited, std::vector<int> &components, int count)
{
    visited[node] = true;
    components[node] = count;
    for (auto next_node : graph.adjList[node])
    {
        if (!visited[next_node.first])
            dfs(graph, next_node.first, visited, components, count);
    }
}

std::pair<int, std::vector<int>> findComponents(networks::Graph &graph, std::vector<bool> &visited, int count=0)
{
    std::vector<int> components(graph.numNodes);
    for (int i=0; i < graph.numNodes; i++)
    {
        if (!visited[i])
        {
            count++;
            dfs(graph, i, visited, components, count);
        }
    }

    return {count, components};
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
    std::cin >> directed >> weighted;

    std::vector<networks::Edge> edges;
    if (weighted)
        for (int i=0; i<numEdges; i++)
        {
            int u, v, w;
            std::cin >> u >> v >> w;
            edges.push_back(networks::Edge(u, v, w)); 
        }

    else
        for (int i=0; i<numEdges; i++)
        {
            int u, v;
            std::cin >> u >> v;
            edges.push_back(networks::Edge(u, v));
        }

    networks::Graph graph = networks::Graph(numNodes, edges);
    std::vector<bool> visited(numNodes, false);

    std::pair<int, std::vector<int>> ans = findComponents(graph, visited);
    std::cout << "No. of connected components: " << ans.first;
    helpers::printVector(ans.second, "The Components array is: ");
}
