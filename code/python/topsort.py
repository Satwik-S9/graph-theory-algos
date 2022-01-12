import helpers as H


# global variables
INPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/input.txt'
OUTPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/output.txt'

# clearing the contents of the file if any
open(OUTPUT_PATH, 'w').close()


def topsort(graph: H.Graph):
    n = graph.num_nodes
    visited = [False for _ in range(n)]
    ordering = [0 for _ in range(n)]
    i = n-1
    
    for node in range(n):
        if not visited[node]:
            wrapper = [visited]  # making a wrapper to pass by reference
            i = dfs(i, node, wrapper, ordering, graph)
            
    return ordering
    
            
def dfs(i, node, v_wrapper, ordering, graph: H.Graph):
    v_wrapper[0][node] = True
    edges = graph.adj_list[node]
    for edge in edges:
        if not v_wrapper[0][edge[0]]:
             i = dfs(i, edge[0], v_wrapper, ordering, graph)
             
    ordering[i] = node
    return i-1

if __name__ == '__main__':
    with open(INPUT_PATH, 'r') as f:
        num_nodes, num_edges = (int(i) for i in f.readline().split(" "))
        directed, weighted = (int(i) for i in f.readline().split(" "))
        
        edges = []
        if weighted:
            for i in range(num_edges):
                u, v, w = (int(i) for i in f.readline().split(" "))
                edges.append(H.Edge(u, v, w))
        else:
            for i in range(num_edges):
                u, v = (int(i) for i in f.readline().split(" "))
                edges.append(H.Edge(u, v))
                
    graph = H.Graph(num_nodes, edges, directed)
    
    ordering = topsort(graph)
    with open(OUTPUT_PATH, 'a') as f:
        f.write(f"{ordering}")