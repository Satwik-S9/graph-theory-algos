// package com.agorithms.GraphTheory;

import java.util.*;

public class DFSI {
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

    static class Graph{
        int numNodes;
        ArrayList<LinkedList<Edge>> adjList = new ArrayList<LinkedList<Edge>>();

        public Graph(int numNodes, List<Edge> edges, boolean directed){
            this.numNodes = numNodes;

            for (int i=0; i<numNodes; ++i)
                adjList.add(new LinkedList<Edge>());

            for (Edge edge : edges){
                adjList.get(edge.src).add(edge);
                if (!directed)
                    adjList.get(edge.dest).add(edge);
            }
        }
    }

    static void dfs(Graph graph, boolean[] visited, int v){
        Stack<Integer> stack = new Stack<>();
        stack.add(v);
        visited[v] = true;

        while(!stack.isEmpty()){
            int node = stack.pop();
            System.out.println(node);

            for (Edge u : graph.adjList.get(node)){
                if (!visited[u.dest])
                    stack.add(u.dest);
                    visited[u.dest] = true;
            }
        }
    }

    static long dfsCountNode(Graph graph, boolean[] visited, int v){
        Stack<Integer> stack = new Stack<>();
        stack.add(v);
        visited[v] = true;
        long count = 0;

        while (!stack.isEmpty()){
            int node = stack.pop();
            count++;

            for (Edge u : graph.adjList.get(node)){
                if (!visited[u.dest])
                    stack.add(u.dest);
                visited[u.dest] = true;
            }
        }

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
                dfs(graph, visited1, i);
        }

        long count = 0;
        boolean[] visited2 = new boolean[numNodes];

        for (int i=0; i<numNodes; i++){
            if (!visited2[i])
                count += dfsCountNode(graph, visited2, i);
        }

        System.out.println("\nThe number of nodes counted by DFS: " + count);
    }
}
