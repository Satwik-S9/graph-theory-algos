package com.agorithms.GraphTheory;


import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

public class findComponents {
    // edge class to represent an edge of the graph
    static class Tuple {
        int a, b;

        public Tuple(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }

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

    static class Graph {
        int numNodes;
        HashMap<Integer, List<Tuple>> adjList = new HashMap<>();

        public Graph(int numNodes, List<Edge> edges, boolean directed) {
            this.numNodes = numNodes;
            for (Edge edge : edges) {
                adjList.get(edge.src).add(new Tuple(edge.dest, edge.cost));
                if (!directed)
                    adjList.get(edge.dest).add(new Tuple(edge.src, edge.cost));
            }
        }
    }


    public static void main(String[] args) throws FileNotFoundException {
//        File file = new File("\\\\wsl$\\Ubuntu-20.04\\home\\freyr\\dev\\GraphTheory\\code\\java\\GraphTheory\\src\\com\\agorithms\\GraphTheory\\input.txt");
//        sc.useDelimiter("\\Z");
        Scanner sc = new Scanner(System.in);
        int numNodes, numEdges;

        System.out.println("Enter Num Nodes, Num Edges ...");
        numNodes = sc.nextInt();
        numEdges = sc.nextInt();

        System.out.println("Enter if the graph is directed, weighted ...");
        boolean directed = sc.nextBoolean();
        boolean weighted = sc.nextBoolean();

        List<Edge> edges = new ArrayList<>();
        if (weighted) {
            for (int i = 0; i < numEdges; i++) {
                int u, v, w;
                u = sc.nextInt();
                v = sc.nextInt();
                w = sc.nextInt();
                edges.add(i, new Edge(u, v, w));
            }
        }
        else {
            for (int i=0; i< numEdges; i++) {
                int u, v;
                u = sc.nextInt();
                v = sc.nextInt();
                edges.add(i, new Edge(u, v));
            }
        }

        Graph graph = new Graph(numNodes, edges, directed);
        boolean[] visited = new boolean[numNodes];

        int ans = find_components(graph, visited, 0);

        System.out.println("The number of components in the Graph is: " + ans);
    }

    static void dfs(Graph graph, boolean[] visited, int v, int[] components, int count){
        visited[v] = true;
        components[v] = count;

        for (Tuple u : graph.adjList.get(v)) {
            if (!visited[u.a])
                dfs(graph, visited, u.a, components, count);
        }
    }

    static int find_components(Graph graph, boolean[] visited, int count) {
        int[] components = new int[graph.numNodes];
        for(int i=0; i < graph.numNodes; i++) {
            if (!visited[i]) {
                count++;
                dfs(graph, visited, i, components, count);
            }
        }
        return count;
    }
}
