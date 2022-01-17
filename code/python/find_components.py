import helpers as H

# global variables
INPUT_PATH = 'input.txt'
OUTPUT_PATH = 'output.txt'

# clearing the contents of the file if any
open(OUTPUT_PATH, 'w').close()


def dfs(graph: H.Graph, node: int, visited: list, componets: list, count: int):
    visited[node] = True
    componets[node] = count
    
    for next_node in graph.adj_list[node]:
        if not visited[next_node[0]]:
            dfs(graph, next_node[0], visited, componets, count)
            
            
def find_components(graph: H.Graph, visited: list, count=0):
    components = [None for _ in range(graph.num_nodes)]
    for i in range(graph.num_nodes):
        if not visited[i]:
            count += 1
            dfs(graph, i, visited, components, count)
            
    return count, components


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
    visited = [False for _ in range(num_nodes)]
        
    ans = find_components(graph, visited)
    with open(OUTPUT_PATH, 'a') as f:
        f.write(f"Number of Components: {ans[0]}\nComponents Array: {ans[1]}")