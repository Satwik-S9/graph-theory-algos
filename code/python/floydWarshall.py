import helpers as H

# global variables
INPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/input.txt'
OUTPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/output.txt'
INF = float('inf')

# clearing the contents of the file if any
open(OUTPUT_PATH, 'w').close()

def floyd_warshall(graph: H.Graph, src: int, dest: int):
    memo = [[0 for _ in range(graph.num_nodes+1)] for _ in range(graph.num_nodes+1)]
    parents = [[None for _ in range(graph.num_nodes+1)] for _ in range(graph.num_nodes+1)]
    
    # deep copy of the adjMatrix and setting up parents array
    for i in range(graph.num_nodes):
        for j in range(graph.num_nodes):
            memo[i][j] = graph.adj_matrix[i][j]
            if graph.adj_matrix[i][j] != INF:
                parents[i][j] = j
                
    for k in range(0, graph.num_nodes):
        for i in range(graph.num_nodes):
            for j in range(graph.num_nodes):
                if (memo[i][k] + memo[k][j] < memo[i][j]):
                    memo[i][j] = memo[i][k] + memo[k][j]
                    parents[i][j] = parents[i][k]
                
    memo, parents = propogate_neg_cycles(memo, parents, graph.num_nodes)
    path = reconstruct_path(memo, parents, src, dest)
    
    return path, memo

    
def propogate_neg_cycles(memo, parents, n):
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if memo[i][k] + memo[k][j] < memo[i][j]:
                    memo[i][j] = -INF 
                    parents[i][j] = -1
                    
    return memo, parents
    

def reconstruct_path(memo, parents, src, dest):
    path = []
    if (memo[src][dest] == INF): return path;
    
    i = src
    while i != dest:
        if (i == -1): return path;
        
        path.append(i)
        i = parents[i][dest]

    if (parents[i][dest] == -1): return None;
    path.append(dest);

    return path


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
        
    graph = H.Graph(num_nodes, edges, directed, init_matrix=True)

    ans = floyd_warshall(graph, 0, 6)
    with open(OUTPUT_PATH, 'a') as f:
        for row in ans[1]:
            f.write(f"{row}\n")