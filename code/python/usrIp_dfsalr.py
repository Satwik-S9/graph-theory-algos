# global variables
input_path = '/home/freyr/dev/GraphTheory/code/python/input.txt'
output_path = '/home/freyr/dev/GraphTheory/code/python/output.txt'

# clearing the contents of the file if any
open(output_path, 'w').close()

class Edge:
    def __init__(self, src, dest, cost=1):
        self.src = src
        self.dest = dest
        self.cost = cost
        
    def __repr__(self) -> str:
        return f"Edge({self.src}, {self.dest}, {self.cost}"
    
    def __str__(self) -> str:
        return repr(self)
    

class Graph:
    def __init__(self, num_nodes, edges, directed=False):
        self.num_nodes = num_nodes
        self.adj_list = {i: [] for i in range(self.num_nodes)}
        
        for edge in edges:
            self.adj_list[edge.src].append((edge.dest, edge.cost))
            if not directed:
                self.adj_list[edge.dest].append((edge.src, edge.cost))
                
def dfs(graph, visited, node=0):
    visited[node] = True
    
    # write to file
    with open(output_path, "a") as f:
        f.write(f"{node} ")
        # print(node, end=" ")
    
    for u in graph.adj_list[node]:
        if not visited[u[0]]:
            dfs(graph, visited, u[0])
            
def dfs_count_node(graph, visited, node=0):
    if visited[node]: return 0
    
    visited[node] = True
    count = 1
    
    for u in graph.adj_list[node]:
        if not visited[u[0]]:
            count += dfs_count_node(graph, visited, u[0])
            
    return count


if __name__ == '__main__':

    
    with open(input_path, "r") as f:
    
        # print("Enter no. of Nodes and no. of Edges in the graph ...")
        num_nodes, num_edges = (int(i) for i in f.readline().split(" "))
        
        # print("Is the Graph directed and weighted (0/1) ...")
        directed, weighted = (int(i) for i in f.readline().split(" "))
        
        # print(weighted, type(weighted), directed, type(directed))
    
        edges = []
        if weighted:
            for _ in range(num_edges):
                u, v, w = (int(i) for i in f.readline().split(" "))
                edges.append(Edge(u, v, w))
        else:
            for _ in range(num_edges):
                u, v = (int(i) for i in f.readline().split(" "))
                edges.append(Edge(u, v))  
            
    graph = Graph(num_nodes, edges)
    visited1 = [False for _ in range(num_nodes)]
    visited2 = [False for _ in range(num_nodes)]
    count = 0
    
    # Output Indicator
    with open(output_path, "a") as f:
        f.write(f"\nPROGRAM OUTPUT STARTS HERE:\n\n")
    
    for i in range(num_nodes):
        if not visited1[i]:
            dfs(graph, visited1, i);
        if not visited2[i]:
            count += dfs_count_node(graph, visited2, i);
    
    with open(output_path, "a") as f:
        f.write(f"\nNumber of nodes counted by dfs: {count}\n")
    
    # print("\nNodes counted by dfs: {}".format(count))