#include<iostream>

#include<map>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>


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

void dfs(Graph &graph, std::vector<bool> &visited, int v=0)
{
    std::stack<int> s;    
    s.push(v);
    visited[v] = true;

    while(!s.empty())
    {
        int node = s.top();
        s.pop();
        std::cout << node << " ";
        // if (visited[node]) continue;

        for (auto u : graph.adjList[node])
        {
            if (!visited[u.first])
            {
                s.push(u.first);
                visited[u.first] = true;
            }                
        }
    }
}

// finding connected components in the graph
long dfsCountNode(Graph &graph, std::vector<bool> &visited, int v=0)
{
    std::stack<int> s;
    s.push(v);
    visited[v] = true;
    long count = 0;

    while(!s.empty())
    {
        int node = s.top();
        s.pop();
        count++;
        // if (visited[node]) continue;

        for (auto u : graph.adjList[node])
        {
            if (!visited[u.first])
            {
                s.push(u.first);
                visited[u.first] = true;
            }
        }
    }

    return count;
}


int main()
{
#ifndef FILE_INPUT
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int numNodes, numEdges;
    // std::cout << "Enter no. of Nodes and no. of Edges in the graph ...\n";
    std::cin >> numNodes >> numEdges;

    bool directed, weighted;
    // std::cout << "Is the Graph weighted and directed (0/1) ...\n";
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
    return 0;
}