// package com.agorithms.GraphTheory;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;


public class dfsALRP {

    // edge class to represent an edge of the graph
    static class Edge{
        int src, dest, cost;

        public Edge(int src, int dest, int cost){
            this.src = src;
            this.dest = dest;
            this.cost = cost;
        }

        // overloading
        public Edge(int src, int dest){
            this(src, dest, 1);
        }

    }

    // Graph class for representing a graph
    static class Graph{
        int numNodes;
        LinkedList<Integer> adjList[];
        // constructor
        public Graph(int numNodes, List<Edge> edges, boolean directed){
            this.numNodes = numNodes;
            adjList = new LinkedList[numNodes];

            for (int i=0; i<numNodes; ++i)
                adjList[i] = new LinkedList<>();

            for (Edge edge : edges){
                adjList[edge.src].add(edge.dest);  // some problem in this line
                if (!directed)
                    adjList[edge.dest].add(edge.src);
            }
        }
    }

    static void dfs(Graph graph, int v, boolean[] visited){
        // set node v to visited and print it out
        visited[v] = true;
        System.out.printf("%d ", v);

        for (int t : graph.adjList[v]){
            if (!visited[t]) dfs(graph, t, visited);
        }
    }

    static long dfsCount(Graph graph, int v, boolean[] visited){
        if (visited[v]) return 0L;

        visited[v] = true;
        long count = 1;

        for (int t : graph.adjList[v])
            if (!visited[t])
                count += dfsCount(graph, t, visited);

        return count;
    }

    public static void main(String[] args){
        // defining initial parameters
        int numNodes = 13;
        int[] e = {1, 2, 1, 7, 1, 8, 2, 3, 2, 6, 3, 4, 3, 5, 8, 9, 8, 12, 9, 10, 9, 11};
        boolean[] visited1 = new boolean[numNodes];
        List<Edge> edges = new ArrayList<>();

        for (int i=0; i<e.length-2; i+=2){
            edges.add(new Edge(e[i], e[i+1]));
        }

        Graph graph = new Graph(numNodes, edges, false);

        for (int i=0; i<numNodes; i++){
            if (!visited1[i])
                dfs(graph, i, visited1);
        }

        long count = 0;
        boolean[] visited2 = new boolean[numNodes];

        for (int i=0; i<numNodes; i++){
            if (!visited2[i])
                count += dfsCount(graph, i, visited2);
        }

        System.out.println("\n The number of nodes counted by DFS: " + count);
    }
}
