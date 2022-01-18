#include <iostream>

#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "helpers.h"


struct myComp 
{
    constexpr bool operator()(std::pair<int, int> const& a, std::pair<int, int> const& b)
    const noexcept
    { return a.second > b.second; }
};


typedef std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, myComp> min_heap;
std::vector<int> djikstra(networks::Graph &graph, int start)
{
    std::vector<bool> visited(graph.numNodes, false);
    std::vector<int> distance(graph.numNodes, INT32_MAX);

    distance[start] = 0;

    min_heap pq;  // priority queue as a min_heap or vice a versa
    pq.push({start, 0});

    while (!pq.empty())
    {
        std::pair<int, int> elem = pq.top(); 
        pq.pop();

        int minValue = elem.second, index = elem.first;
        visited[index] = true;

        if (distance[index] < minValue) continue;
        for (auto edge : graph.adjList[index])
        {
            if (visited[edge.first]) continue;
            int newDist = distance[index] + edge.second;

            if (newDist < distance[edge.first])
            {
                distance[edge.first] = newDist;
                pq.push({edge.first, newDist});
            }
        }
    }

    return distance;
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

    std::vector<int> dist = djikstra(graph, 0);
    helpers::printVector(dist);
    helpers::printGraph(graph);
}