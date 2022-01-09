# global variables
INPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/input.txt'
OUTPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/output.txt'

# clearing the contents of the file if any
open(OUTPUT_PATH, 'w').close()


class Edge:
    def __init__(self, src, dest, cost=1):
        self.src = src
        self.dest = dest
        self.cost = cost
        

class Graph:
    def __init__(self, num_nodes, edges, directed=False):
        self.num_nodes = num_nodes
        self.adj_list = {x : [] for x in range(num_nodes)}
        
        for edge in edges:
            self.adj_list[edge.src].append((edge.dest, edge.cost))
            if not directed:
                self.adj_list[edge.dest].append((edge.src, edge.cost))
                

def dfs(graph, visited, v=0):
    stack = []
    stack.append(v)
    visited[v] = True
    
    while(len(stack) != 0):
        node = stack.pop()
        
        # printing out the node
        with open(OUTPUT_PATH, "a") as f:
            f.write(f"{node} ")
        
        for u in graph.adj_list[node]:
            if not visited[u[0]]:
                stack.append(u[0])
                visited[u[0]] = True

def dfs_count(graph, visited, v=0):
    stack = []
    stack.append(v)
    visited[v] = True
    count = 0
    
    while(len(stack) != 0):
        node = stack.pop()
        count += 1
        
        for u in graph.adj_list[node]:
            if not visited[u[0]]:
                stack.append(u[0])
                visited[u[0]] = True
                
    return count


if __name__ == '__main__':
    
    with open(INPUT_PATH, "r") as f:
        num_nodes, num_edges = (int(i) for i in f.readline().split(" "))
        directed, weighted = (int(i) for i in f.readline().split(" "))
        
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
    with open(OUTPUT_PATH, "a") as f:
        f.write("\nPROGRAM OUTPUT STARTS HERE:\n\n")
        
    for i in range(num_nodes):
        if not visited1[i]:
            dfs(graph, visited1, i)
            
        if not visited2[i]:
            count += dfs_count(graph, visited2, i)
            
    with open(OUTPUT_PATH, "a") as f:
        f.write(f"\nNo. of Nodes: {count}")