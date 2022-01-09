#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<map>

// data structure to store an edge
struct Edge
{
    int src, dest, cost;

    // constructor
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

    // constrcutor
    Graph(int numNodes, std::vector<Edge> const &edges, bool directed=false)
    {
        this->numNodes = numNodes;

        for (auto &edge : edges)
        {
            adjList[edge.src].push_back({edge.dest, edge.cost});
            
            if (!directed)
                adjList[edge.dest].push_back({edge.src, edge.cost});
        }       
    }
};

void dfs(Graph &graph, std::vector<bool> &visited, int v=0)
{
    // mark node as visited and print its value
    visited[v] = true;
    std::cout << v << " ";

    // for each neighbour in adj. List of v call dfs
    // std::pair<int, int> instead of auto 
    for (auto u : graph.adjList[v])
    {
        if (!visited[u.first])
            dfs(graph, visited, u.first);
    }
}

long dfsCountNode(Graph &graph, std::vector<bool> &visited, int v=0)
{
    if (visited[v]) return 0l;

    // mark node as visited 
    visited[v] = true;
    long count = 1;

    // for each u in adj. List of v call dfs and add return value to count
    for (std::pair<int, int> u : graph.adjList[v])
    {
        if (!visited[u.first])
            count += dfsCountNode(graph, visited, u.first);
    }

    return count;
}


int main()
{
    int numNodes, numEdges;
    std::cout << "Enter no. of Nodes and no. of Edges in the graph ...\n";
    std::cin >> numNodes >> numEdges;

    bool directed, weighted;
    std::cout << "Is the Graph weighted and directed (0/1) ...\n";
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

    // Initializing Graph and visited array
    Graph graph = Graph(numNodes, edges, directed);
    std::vector<bool> visited1(numNodes, false);
    std::vector<bool> visited2(numNodes, false);


    long count = 0;

    for (int i=0; i<numNodes; i++)
    {
        if (!visited1[i])
            dfs(graph, visited1, i);
        if (!visited2[i])
            count += dfsCountNode(graph, visited2, i);
    }

    std::cout << "\nNumber of nodes: " << count; 
}   