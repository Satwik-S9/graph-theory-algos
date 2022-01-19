#include <iostream>

#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "helpers.h"


std::pair<std::vector<int>, std::vector<int>> djikstra(networks::Graph &graph, int start)
{
    std::vector<bool> visited(graph.numNodes, false);
    std::vector<int> distance(graph.numNodes, INT32_MAX);
    std::vector<int> parents(graph.numNodes, -1);
    
    distance[start] = 0;

    networks::IndexedMinPQ ipq = networks::IndexedMinPQ(graph.numNodes);  
    ipq.push(start, 0);

    while (!ipq.isEmpty())
    {
        std::pair<int, int> elem = ipq.pop(); 
        
        int minValue = elem.second, index = elem.first;
        ipq.deleteKey(index);
        visited[index] = true;

        if (distance[index] < minValue) continue;
        for (auto edge : graph.adjList[index])
        {
            if (visited[edge.first]) continue;
            int newDist = distance[index] + edge.second;

            if (newDist < distance[edge.first])
            {
                parents[edge.first] = index;
                distance[edge.first] = newDist;

                if (!ipq.contains(edge.first))
                    ipq.push(edge.first, newDist);
                else
                    ipq.decreaseKey(edge.first, newDist);
            }
        }
    }

    return {distance, parents};
}

std::pair<int, std::vector<int>> shortest_path(networks::Graph &graph, int start, int target)
{
    std::pair<std::vector<int>, std::vector<int>> ans = djikstra(graph, start);
    std::vector<int> path;
    if (ans.first[target] == INT32_MAX) return {-1, path};

    int node = target;
    while (node != -1)
    {
        path.push_back(node);
        node = ans.second[node];
    }
    std::reverse(path.begin(), path.end());
    return {ans.first[target], path};
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

    // Initializing Graph
    networks::Graph graph = networks::Graph(numNodes, edges, directed);

    std::pair<std::vector<int>, std::vector<int>> ans = djikstra(graph, 0);
    helpers::printVector(ans.first, "Distance Array: ");
    helpers::printVector(ans.second, "Parents Array: ");

    std::pair<int, std::vector<int>> ans_sp = shortest_path(graph, 0, 5);
    std::cout << "Shortest Distance: " << ans_sp.first << "\n";
    helpers::printVector(ans_sp.second, "Shortest Path: ");
}