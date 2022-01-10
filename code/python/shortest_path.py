import helpers as H


# global variables
INPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/input.txt'
OUTPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/output.txt'

# clearing the contents of the file if any
open(OUTPUT_PATH, 'w').close()


def bfs(graph: H.Graph, visited: list, v: int, suppress: bool=True):
    que = []
    que.append(v)
    visited[v] = True
    parents = [None for _ in range(len(graph.adj_list))]
    
    if not suppress:
        with open(OUTPUT_PATH, 'a') as f:
            f.write("Order of Traversal BFS: ")
    
    while len(que) != 0:
        node = que.pop(0)
        if not suppress:
            with open(OUTPUT_PATH, 'a') as f:
                f.write(f"{node} ")

        for u in graph.adj_list[node]:
            if not visited[u[0]]:
                que.append(u[0])
                visited[u[0]] = True
                parents[u[0]] = node
                
    return parents
                
def shortest_path(graph: H.Graph, start: int, end: int):
    visited = [False for _ in range(len(graph.adj_list))]
    parents = bfs(graph, visited, start)
    
    return reconstruct_path(start, end, parents)

def reconstruct_path(start, end, parents):
    path = []
    i = end
    while i is not None:
        path.append(i)
        i = parents[i]
        
    path = path[::-1]
    
    if path[0] == start:
        return path
    
    return [-1]


if __name__ == '__main__':
    with open(INPUT_PATH, 'r') as f:
        num_nodes, num_edges = (int(i) for i in f.readline().split(" "))
        directed, weighted = (int(i) for i in f.readline().split(" "))
        
        edges = []        
        if weighted:
            for _ in range(num_edges):
                u, v, w = (int(i) for i in f.readline().split(" "))
                edges.append(H.Edge(u, v, w))
        else:
            for _ in range(num_edges):
                u, v= (int(i) for i in f.readline().split(" "))
                edges.append(H.Edge(u, v))

    graph = H.Graph(num_nodes, edges)
    visited = [False for _ in range(num_nodes)]
    
    bfs(graph, visited, 0, False)
    path = shortest_path(graph, 0, 3)
    
    with open(OUTPUT_PATH, 'a') as f:
        f.write(f"\nShortest path from 0 -> 3: {path}")
