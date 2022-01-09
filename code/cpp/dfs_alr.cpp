#include <set>
#include <map>
#include <list>
#include <stack>
#include <string>
#include <vector>

#include <iostream>

// data structure to store graph edge
struct Edge
{
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
    std::map<int, std::vector<std::pair<int, int>>> adj_list;

    // constructor
    Graph(std::vector<Edge> const &edges)
    {
        for (auto &edge : edges)
        {
            adj_list[edge.src].push_back({edge.dest, edge.cost});
            adj_list[edge.dest].push_back({edge.src, edge.cost});
        }
    }
};

void dfs(Graph &graph, int v, std::vector<bool> &visited)
{
    // mark the current node as visited
    visited[v] = true;

    // print the current node
    std::cout << v << " ";

    // do for every edge in the graph
    for (auto u : graph.adj_list[v])
    {
        if (!visited[u.first])
        {
            dfs(graph, u.first, visited);
        }
    }    
}

long dfs_count(Graph &graph, int v, std::vector<bool> &visited)
{
    if (visited[v]) return 0l;

    visited[v] = true;
    long count = 1;

    for (auto u : graph.adj_list[v])
    {
        if (!visited[u.first])
        {
            count += dfs_count(graph, u.first, visited);
        }
    }    

    return count;
}


int main()
{
    // vector of graph edges as per the above diagram
    std::vector<Edge> edges = {
        // Notice that node 0 is unconnected
        Edge(1, 2), Edge(1, 7), Edge(1, 8), Edge(2, 3), Edge(2, 6), Edge(3, 4),
        Edge(3, 5), Edge(8, 9), Edge(8, 12), Edge(9, 10), Edge(9, 11)
    };

    int n = 13;
    Graph graph(edges);

    std::vector<bool> visited(n);

    // Perform DFS traversal from all undiscovered nodes to
    // cover all connected components of a graph
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == false) {
            dfs(graph, i, visited);
        }
    }

    long count = 0;
    std::vector<bool> visited2(n);
    for (int i = 0; i < n; i++)
    {
        if (visited2[i] == false) {
            count += dfs_count(graph, i, visited2);
        }
    }

    std::cout << "\n" << count;
}