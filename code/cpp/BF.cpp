#include <iostream>

#include <map>
#include <climits>
#include <vector>
#include <string>
#include <algorithm>

// defining necessary support data structure
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


std::vector<int> bellmanFord(Graph &graph, int start)
{
    std::vector<int> distance(graph.numNodes, INT_MAX);

    distance[start] = 0;

    for (int i=start; i < graph.numNodes-1; i++)
    {
        for (auto edges : graph.adjList)
            for (auto edge : edges.second)
                if (distance[edge.src] + edge.cost < distance[edge.dest])
                    distance[edge.dest] = distance[edge.src] + edge.cost;
    }

    // check for negative cycles
    for (int i=start; i < graph.numNodes-1; i++)
    {
        for (auto iter : graph.adjList)
            for (auto edge : graph.adjList[iter.first])
                if (distance[edge.src] + edge.cost < edge.dest)
                    distance[edge.dest] = INT_MIN; 
    }

    return distance;
}
//todo: Add shortest path method having reconstruct path and target.


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

    std::vector<int> distance = bellmanFord(graph, 0);

    for (int i=0; i<numNodes; i++)
    std::cout << distance[i] << " ";

    return 0;
}
