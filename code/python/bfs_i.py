import helpers as H


# global variables
INPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/input.txt'
OUTPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/output.txt'

# clearing the contents of the file if any
open(OUTPUT_PATH, 'w').close()


def bfs(graph: H.Graph, visited: list, v: int):
    que = []
    que.append(v)
    visited[v] = True

    while len(que) != 0:
        node = que.pop(0)
        with open(OUTPUT_PATH, 'a') as f:
            f.write(f"{node} ")

        for u in graph.adj_list[node]:
            if not visited[u[0]]:
                que.append(u[0])
                visited[u[0]] = True


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
    
    bfs(graph, visited, 0)
    

