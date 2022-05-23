#pragma once

#include <map>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


namespace networks {
    
    #define INF 1e7
    
    class Edge
    {
    public:
        int src, dest, cost;

        Edge(int s, int d, int c = 1)
        {
            src = s;
            dest = d;
            cost = c;
        }
    };

    class Graph
    {
    public:
        int numNodes, numEdges;
        std::map<int, std::vector<std::pair<int, int>>> adjList; // adjacency list
        std::vector<std::vector<int>> adjMatrix;  // adjacency matrix

        Graph(int numNodes, std::vector<Edge> &edges, bool directed=false, bool init_matrix=false)
        {
            this->numNodes = numNodes;
            numEdges = edges.size();
            if (!init_matrix)
                for (Edge &edge : edges)
                {
                    adjList[edge.src].push_back({edge.dest, edge.cost});
                    if (!directed)
                        adjList[edge.dest].push_back({edge.src, edge.cost});
                }

            if (init_matrix)
            {
                std::vector<std::vector<int>> adjMatrix(numNodes, std::vector<int>(numNodes, INF));
                for (Edge &edge : edges)
                {
                    adjMatrix[edge.src][edge.dest] = edge.cost;
                    if (!directed)
                        adjMatrix[edge.dest][edge.src] = edge.cost;
                }
                this->adjMatrix = adjMatrix;
            }
        }
    };

    class IndexedMinPQ
    {
        int NMAX, N, *heap, *index, *keys;

        void swap(int i, int j)
        {
            int t = heap[i];
            heap[i] = heap[j];
            heap[j] = t;
            index[heap[i]] = i;
            index[heap[j]] = j;
        }

        void bubbleUp(int k)
        {
            while (k > 1 && keys[heap[k / 2]] > keys[heap[k]])
            {
                swap(k, k / 2);
                k = k / 2;
            }
        }

        void bubbleDown(int k)
        {
            int j;
            while (2 * k <= N)
            {
                j = 2 * k;
                if (j < N && keys[heap[j]] > keys[heap[j + 1]])
                    j++;
                if (keys[heap[k]] <= keys[heap[j]])
                    break;
                swap(k, j);
                k = j;
            }
        }

    public:
        // Create an empty MinIndexedPQ which can contain atmost NMAX elements
        IndexedMinPQ(int NMAX)
        {
            this->NMAX = NMAX;
            N = 0;
            keys = new int[NMAX + 1];
            heap = new int[NMAX + 1];
            index = new int[NMAX + 1];
            for (int i = 0; i <= NMAX; i++)
                index[i] = -1;
        }

        ~IndexedMinPQ()
        {
            delete[] keys;
            delete[] heap;
            delete[] index;
        }

        // check if the PQ is empty
        bool isEmpty()
        {
            return N == 0;
        }

        // check if i is an index on the PQ
        bool contains(int i)
        {
            return index[i] != -1;
        }

        // return the number of elements in the PQ
        int size()
        {
            return N;
        }

        // associate key with index i; 0 < i < NMAX
        void push(int i, int key)
        {
            N++;
            index[i] = N;
            heap[N] = i;
            keys[i] = key;
            bubbleUp(N);
        }

        std::pair<int, int> pop()
        {
            return {heap[1], keys[heap[1]]};
        }

        // returns the index associated with the minimal key
        int minIndex()
        {
            return heap[1];
        }

        // returns the minimal key
        int minKey()
        {
            return keys[heap[1]];
        }

        // delete the minimal key and return its associated index
        // Warning: Don't try to read from this index after calling this function
        int deleteMin()
        {
            int min = heap[1];
            swap(1, N--);
            bubbleDown(1);
            index[min] = -1;
            heap[N + 1] = -1;
            return min;
        }

        // returns the key associated with index i
        int keyOf(int i)
        {
            return keys[i];
        }

        // change the key associated with index i to the specified value
        void changeKey(int i, int key)
        {
            keys[i] = key;
            bubbleUp(index[i]);
            bubbleDown(index[i]);
        }

        // decrease the key associated with index i to the specified value
        void decreaseKey(int i, int key)
        {
            keys[i] = key;
            bubbleUp(index[i]);
        }

        // increase the key associated with index i to the specified value
        void increaseKey(int i, int key)
        {
            keys[i] = key;
            bubbleDown(index[i]);
        }

        // delete the key associated with index i
        void deleteKey(int i)
        {
            int ind = index[i];
            swap(ind, N--);
            bubbleUp(ind);
            bubbleDown(ind);
            index[i] = -1;
        }
    };
}

namespace helpers
{
    template <typename T>
    void printVector(std::vector<T> &v, std::string message = "")
    {
        std::cout << "\n"
                  << message;
        for (T e : v)
            std::cout << e << " ";
        std::cout << std::endl;
    }

    template <typename T>
    void printArray(T arr[], std::string message = "")
    {
        int size = *(&arr + 1) - arr;
        std::cout << "\n"
                  << message;
        for (int i = 0; i < size; i++)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
    }

    void printGraph(networks::Graph &graph)
    {
        std::cout << "\nAdjacency List of the graph: \n";
        // std::cout << "NODE  NEIGHBOURS (node, cost)\n";
        for (int i = 0; i < graph.numNodes; i++)
        {
            std::cout << i << ": ";
            for (auto edge : graph.adjList[i])
            {
                std::cout << "(" << edge.first << ", " << edge.second << "), ";
            }
            std::cout << std::endl;
        }
    }
}