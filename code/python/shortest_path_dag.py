import helpers as H

# global variables
INPUT_PATH = 'input.txt'
OUTPUT_PATH = 'output.txt'

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


def shortest_path_dag(graph: H.Graph, start, target=-1):
    if target == -1: target = graph.num_nodes - 1
    
    ordering = topsort(graph)
    distance = [float('inf') for _ in range(graph.num_nodes)]
    distance[start] = 0
    
    for i in range(graph.num_nodes):
        node_index = ordering[i]
        adj_edges = graph.adj_list[node_index]
        for edge in adj_edges:
            new_dist = distance[node_index] + edge[1]
            if distance[edge[0]] == float('inf'): distance[edge[0]] = new_dist 
            else: distance[edge[0]] = min(distance[edge[0]], new_dist)
            
    return distance, distance[target]
    
    
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
    
    ans = shortest_path_dag(graph, 0)
    with open(OUTPUT_PATH, 'a') as f:
        f.write(f"{ans}")