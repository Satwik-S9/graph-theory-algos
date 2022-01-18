#pragma once

#include<map>
#include<queue>
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>

namespace networks
{
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

    class Graph
    {
    public:
        int numNodes;
        std::map<int, std::vector<std::pair<int, int>>> adjList;

        Graph(int numNodes, std::vector<Edge> &edges, bool directed=false)
        {
            this->numNodes = numNodes;
            for (Edge &edge: edges)
            {
                adjList[edge.src].push_back({edge.dest, edge.cost});
                if (!directed)
                    adjList[edge.dest].push_back({edge.src, edge.cost});
            }
        }
    };
}

namespace helpers
{
    template <typename T>
    void printVector(std::vector<T> &v, std::string message="")
    {
        std::cout << "\n" << message;
        for (T e : v)
            std::cout << e << " ";
        std::cout << std::endl;
    }

    template <typename T>
    void printArray(T arr[], std::string message="")
    {
        int size = *(&arr + 1) - arr;
        std::cout << "\n" << message;
        for (int i=0; i<size; i++)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
    }

    void printGraph(networks::Graph &graph)
    {
        std::cout << "\nAdjacency List of the graph: \n";
        // std::cout << "NODE  NEIGHBOURS (node, cost)\n";
        for (int i=0; i<graph.numNodes; i++)
        {
            std::cout << i << ": ";
            for (auto edge : graph.adjList[i])
            {
                std::cout << "(" << edge.first << ", " << edge.second << "), ";
            } std::cout << std::endl;
        }
    }
}