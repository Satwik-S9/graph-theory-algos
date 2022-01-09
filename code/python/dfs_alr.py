class Edge:
    def __init__(self, src, dest, cost=1):
        self.src = src
        self.dest = dest
        self.cost = cost    
        
class Graph:
    def __init__(self, num_nodes, edges, directed=False):
        self.adj_list = [[] for _ in range(num_nodes)]
        
        for edge in edges:
            self.adj_list[edge.src].append((edge.dest, edge.cost))
            if not directed:
                self.adj_list[edge.dest].append((edge.src, edge.cost))
            
                
def dfs(graph: Graph, v: int, visited: list):
    # mark the current node as visited
    visited[v] = True
    
    # print the current node
    print(v, end=" ")
    
    for u in graph.adj_list[v]:
        if not visited[u[0]]:
            dfs(graph, u[0], visited)

# count the number of nodes using dfs
def dfs_count(graph: Graph, v: int, visited: list):
    # mark the current node as visited
    if visited[v]: return 0;
    
    visited[v] = True
    count = 1;
    
    for u in graph.adj_list[v]:
        if not visited[u[0]]:
            count += dfs_count(graph, u[0], visited)
    
    return count
            

if __name__ == '__main__':
    num_nodes = 13
    edges = [
        # notice edge 0 is not connected
        Edge(1, 2), Edge(1, 7), Edge(1, 8), Edge(2, 3), Edge(2, 6), Edge(3, 4),
        Edge(3, 5), Edge(8, 9), Edge(8, 12), Edge(9, 10), Edge(9, 11) #, Edge(0, 1)
    ]

    graph = Graph(num_nodes, edges)
    # print(graph.adj_list)  # debugging statement
    
    visited = [False for _ in range(num_nodes)]
    
    # for all connected and non-connected nodes 
    for i in range(num_nodes):
        if not visited[i]:
            dfs(graph, i, visited)
    
    count = 0
    visited = [False for _ in range(num_nodes)]
    # for all connected and non-connected nodes 
    for i in range(num_nodes):
        if not visited[i]:
            count += dfs_count(graph, i, visited)
            
    print(f"\n{count}")
    