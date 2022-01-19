import helpers as H

# global variables
INPUT_PATH = 'input.txt'
OUTPUT_PATH = 'output.txt'

# clearing the contents of the file if any
open(OUTPUT_PATH, 'w').close()


def djikstra(graph: H.Graph, start: int):
    visited = [False for _ in range(graph.num_nodes)]
    distance = [float('inf') for _ in range(graph.num_nodes)]
    parents = [None for _ in range(graph.num_nodes)]
    
    distance[start] = 0
    ipq = H.IndexedMinPQ(graph.num_nodes)
    ipq.push(start, 0)
    
    while not ipq.is_empty():
        index, min_value = ipq.pop()
        visited[index] = True
        
        if distance[index] < min_value: continue
        
        for edge in graph.adj_list[index]:
            if visited[edge[0]]: continue
        
            new_dist = distance[index] + edge[1]
            if new_dist < distance[edge[0]]:
                parents[edge[0]] = index
                distance[edge[0]] = new_dist
        
                if edge[0] in ipq.heap:
                    ipq.update(edge[0], new_dist)
                else:
                    ipq.push(edge[0], new_dist)
                    
    return distance, parents


def shortest_path(graph: H.Graph, source: int, target: int):
    dist, parents = djikstra(graph, source)
    path = []
    if dist[target] == float('inf'): return path
    
    node = target
    while node is not None:
        path.append(node)
        node = parents[node]

    path = path[::-1]
    return path, dist[target]
        
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
    
    ans = djikstra(graph, 0)
    ans_sp = shortest_path(graph, 0, 5)
    with open(OUTPUT_PATH, 'a') as f:
        f.write(f"Distance Array: {ans[0]}\nParents Array: {ans[1]}\
                \nShortest Path: {ans_sp[0]}\nCost of Shortest Path: {ans_sp[1]}")
