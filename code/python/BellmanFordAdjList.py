# global variables
INPUT_PATH = 'input.txt'
OUTPUT_PATH = 'output.txt'

# clearing the contents of the file if any
open(OUTPUT_PATH, 'w').close()


## === CLASS REPRESENTING AN EDGE === ##
class Edge:
    def __init__(self, src, dest, cost=1):
        self.src = src
        self.dest = dest
        self.cost = cost
        
    def __repr__(self) -> str:
        return f"Edge({self.src}, {self.dest}, {self.cost}"
    
    def __str__(self) -> str:
        return repr(self)

        
## === Slightly Modified GRAPH DATA STRUCTURE === ##
class Graph:
    def __init__(self, num_nodes, edges, directed=False):
        self.num_nodes = num_nodes
        self.adj_list = {i: [] for i in range(self.num_nodes)}
        
        for edge in edges:
            self.adj_list[edge.src].append(edge)
            if not directed:
                self.adj_list[edge.dest].append(edge)
                
    def __repr__(self) -> str:
        return f"{self.adj_list}"
    
    def __str__(self) -> str:
        return repr(self)
    
    
def bellman_ford(graph: Graph, start: int):
    distance = [float('inf') for _ in range(graph.num_nodes)]
    parents = [None for _ in range(graph.num_nodes)]
    distance[start] = 0
    
    # go over the graph
    for _ in range(start, graph.num_nodes-1):
        for _, edges in graph.adj_list.items():
            for edge in edges:
                if (distance[edge.src] + edge.cost < distance[edge.dest]):
                    parents[edge.dest] = edge.src 
                    distance[edge.dest] = distance[edge.src] + edge.cost

    # check for negative cycles
    for _ in range(start, graph.num_nodes-1):
        for _, edges in graph.adj_list.items():
            for edge in edges:
                if (distance[edge.src] + edge.cost < distance[edge.dest]):
                    distance[edge.dest] = -float('inf') 
                    
    return distance, parents

def reconstruct_path(parents, dest):
    path = []
    i = dest
    while i is not None:
        path.append(i)
        i = parents[i]
        
    path = path[::-1]
    return path

def shortest_path(graph, src, dest):
    distance, parents = bellman_ford(graph, src)
    path = reconstruct_path(parents, dest)
    
    # print(f"The Shortest path is: {path}")
    
    return distance[dest], path

def check_neg_cycles(graph):
    distance, _ = bellman_ford(graph, 0)
    if (-float('inf')) in distance:
        return True
    
    return False
    
if __name__ == '__main__':
    with open(INPUT_PATH, 'r') as f:
        num_nodes, num_edges = (int(i) for i in f.readline().split(" "))
        directed, weighted = (int(i) for i in f.readline().split(" "))
        
        edges = []
        if weighted:
            for i in range(num_edges):
                u, v, w = (int(i) for i in f.readline().split(" "))
                edges.append(Edge(u, v, w))
        else:
            for i in range(num_edges):
                u, v = (int(i) for i in f.readline().split(" "))
                edges.append(Edge(u, v))
                
    graph = Graph(num_nodes, edges, directed) 
    
    ans = bellman_ford(graph, 0)
    sp = shortest_path(graph, 0, 8)
    with open(OUTPUT_PATH, 'a') as f:
        f.write(f"Distance Array is: {ans[0]}\nParents Array is: {ans[1]}\n")
        f.write(f"The minimum cost to {8} is: {sp[0]},\nPath is: {sp[1]}")
        if check_neg_cycles(graph):
            f.write("\nThe Graph has Negative Cycles")