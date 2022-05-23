#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "helpers.h"

# define INF 1e7

typedef std::vector<std::vector<int>> matrix;

void propogateNegCycles(matrix &memo, matrix &parents, int n)
{
    for (int k=0; k < n; k++)
    {
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                if (memo[i][k] + memo[k][j] < memo[i][j])
                {
                    memo[i][j] = -INF;
                    parents[i][j] = -2;
                }
    }
}

std::vector<int> reconstructPath(matrix &memo, matrix &parents, int src, int dest)
{
    std::vector<int> path;
    if (memo[src][dest] == INF) return path;
    
    int i=src;
    for (; i != dest; i=parents[i][dest])
    {
        if (i == -2) return {-1, -1};
        path.push_back(i);
    }

    if (parents[i][dest] == -2) return {-1, -1};
    path.push_back(dest);

    return path;
}

std::pair<std::vector<int>, matrix> floydWarshall(networks::Graph &graph, int src, int dest)
{
    matrix memo(graph.numNodes, std::vector<int>(graph.numNodes+1));
    matrix parents(graph.numNodes, std::vector<int>(graph.numNodes+1, -1));
    
    //deep copy of the adjMatrix and setting up parents array
    for (int i=0; i<graph.numNodes; i++)
    {
        for (int j=0; j<graph.numNodes; j++)
        {
            memo[i][j] = graph.adjMatrix[i][j];
            if (graph.adjMatrix[i][j] != INF)
                parents[i][j] = j;
        }
    }

    for (int k=0; k<graph.numNodes; k++)
    {
        for (int i=0; i < graph.numNodes; i++)
            for (int j=0; j < graph.numNodes; j++)
                if (memo[i][k] + memo[k][j] < memo[i][j])
                {
                    memo[i][j] = memo[i][k] + memo[k][j];
                    parents[i][j] = parents[i][k];
                }
    }

    propogateNegCycles(memo, parents, graph.numNodes);

    std::vector<int> path = reconstructPath(memo, parents, src, dest);
    return {path, memo};
    // return memo;
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
 
    networks::Graph graph = networks::Graph(numNodes, edges, true, true);
    std::pair<std::vector<int>, matrix> ans = floydWarshall(graph, 0, 6);
    
    for (int i=0; i<ans.second.size(); i++) {
        for (int j=0; j<ans.second[i].size(); j++) {
            if (ans.second[i][j] == -INF) {
                std::cout << "-INF" << " ";
            }
            else std::cout << ans.second[i][j] << " ";
        } std::cout<<std::endl;
    }
    
    helpers::printVector(ans.first, "The Shortest path is: ");

    return 0;
}