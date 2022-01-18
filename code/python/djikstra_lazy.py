import helpers as H
import heapq

# global variables
INPUT_PATH = 'input.txt'
OUTPUT_PATH = 'output.txt'

# clearing the contents of the file if any
open(OUTPUT_PATH, 'w').close()

def djikstra(graph: H.Graph, start: int):
    visited = [False for _ in range(graph.num_nodes)]
    distance = [float('inf') for _ in range(graph.num_nodes)]
    
    distance[start] = 0
    
    pq = []
    heapq.heappush(pq, (0, start))
    
    while (len(pq) != 0):
        min_value, index = heapq.heappop(pq)
        visited[index] = True
        
        if (distance[index] < min_value): continue
        for edge in graph.adj_list[index]:
            if visited[edge[0]]: continue
            new_dist = distance[index] + edge[1]
            
            if (new_dist < distance[edge[0]]):
                distance[edge[0]] = new_dist
                heapq.heappush(pq, (new_dist, edge[0]))

    return distance


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
    with open(OUTPUT_PATH, 'a') as f:
        f.write(f"Cost Array: {ans}")