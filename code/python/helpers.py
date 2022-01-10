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
                
    def __repr__(self) -> str:
        return f"{self.adj_list}"
    
    def __str__(self) -> str:
        return repr(self)