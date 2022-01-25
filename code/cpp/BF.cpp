#include <iostream>

#include <map>
#include <climits>
#include <vector>
#include <string>
#include <algorithm>
#include "helpers.h"

//* defining necessary support data structure
class Edge
{
public:
    int src, dest, cost;

    Edge(int s, int d, int c=1)
    {
        src = s;
        dest = d;
        cost = c;
    }
};

// little tweaks in the Graph Data Structure
class Graph
{
public:
    int numNodes, numEdges;
    std::map<int, std::vector<Edge>> adjList;

    Graph(int numNodes, std::vector<Edge> &edges, bool directed=false)
    {
        this->numNodes = numNodes;
        numEdges = edges.size();
        for (Edge &edge: edges)
        {
            adjList[edge.src].push_back(edge);
            if (!directed)
                adjList[edge.dest].push_back(edge);
        }
    }
};


std::pair<std::vector<int>, std::vector<int>> bellmanFord(Graph &graph, int start)
{
    std::vector<int> distance(graph.numNodes, INT_MAX);
    std::vector<int> parents(graph.numNodes, -1);

    distance[start] = 0;

    for (int i=start; i < graph.numNodes-1; i++)
    {
        for (auto edges : graph.adjList)
            for (auto edge : edges.second)
                if (distance[edge.src] + edge.cost < distance[edge.dest])
                {
                    parents[edge.dest] = edge.src;
                    distance[edge.dest] = distance[edge.src] + edge.cost;
                }
    }

    // check for negative cycles
    for (int i=start; i < graph.numNodes-1; i++)
    {
        for (auto iter : graph.adjList)
            for (auto edge : graph.adjList[iter.first])
                if (distance[edge.src] + edge.cost < edge.dest)
                    distance[edge.dest] = INT_MIN; 
    }

    return {distance, parents};
}

std::vector<int> reconstructPath(std::vector<int> parents, int dest)
{
    std::vector<int> path;
    int i = dest;
    while (i != -1)
    {
        path.push_back(i);
        i = parents[i];
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

int shortestPath(Graph &graph, int src, int dest)
{
    std::pair<std::vector<int>, std::vector<int>> ans = bellmanFord(graph, src);
    std::vector<int> path = reconstructPath(ans.second, dest);
    helpers::printVector(path, "The Shortest path is: ");

    return ans.first[dest];
}

bool checkNegCycles(Graph &graph)
{
    std::pair<std::vector<int>, std::vector<int>> ans = bellmanFord(graph, 0);
    auto has_cycles = std::find(ans.first.begin(), ans.first.end(), INT_MIN);
    
    if (has_cycles != ans.first.end()) return true;

    return false;
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
    std::vector<Edge> edges;
    if (weighted)
    {
        for (int i=0; i<numEdges; i++)
        {
            std::cin >> u >> v >> w;
            edges.push_back(Edge(u, v, w));
        }
    }
    else
    {
        for (int i=0; i<numEdges; i++)
        {
            std::cin >> u >> v;
            edges.push_back(Edge(u, v));
        }
    }

    Graph graph = Graph(numNodes, edges, directed);

    std::pair<std::vector<int>, std::vector<int>> ans = bellmanFord(graph, 0);

    helpers::printVector(ans.first, "Distance array: ");
    helpers::printVector(ans.second, "Parents array: ");

    int sp = shortestPath(graph, 0, 8);
    std::cout << "Shortest path to " << 8 << " is " << sp;

    if (checkNegCycles(graph)) std::cout << "\nThe Graph has Negative Cycle(s)";

    return 0;
}
