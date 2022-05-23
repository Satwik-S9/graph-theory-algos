INF = float('inf')


## === CLASS REPRESENTING AN EDGE === ##
class Edge:
    def __init__(self, src, dest, cost=1):
        self.src = src
        self.dest = dest
        self.cost = cost

    def __repr__(self) -> str:
        return f"Edge({self.src}, {self.dest}, {self.cost}"

    def __str__(self) -> str:
        return repr(self)


## === GRAPH DATA STRUCTURE === ##
class Graph:
    def __init__(self, num_nodes, edges, directed=False, init_matrix=False):
        self.num_nodes = num_nodes
        self.num_edges = len(edges)
        self.directed = directed
        self.init_matrix = init_matrix

        if not init_matrix:
            self.adj_list = {i: [] for i in range(self.num_nodes)}

            for edge in edges:
                self.adj_list[edge.src].append((edge.dest, edge.cost))
                if not directed:
                    self.adj_list[edge.dest].append((edge.src, edge.cost))

        else:
            self.adj_matrix = [[INF for _ in range(num_nodes)] for _ in range(num_nodes)]

            for edge in edges:
                self.adj_matrix[edge.src][edge.dest] = edge.cost
                if not directed:
                    self.adj_matrix[edge.dest][edge.src] = edge.cost

    def __repr__(self) -> str:
        if self.init_matrix:
            return f"{self.adj_matrix}"
        else:
            return f"{self.adj_list}"

    def __str__(self) -> str:
        return repr(self)


## === INDEXED PRIORITY QUEUE USING MIN-HEAP === ##
class IndexedMinPQ:
    def __init__(self, N) -> None:
        self.N = N+1
        self.key = [None for i in range(self.N)]
        self.heap = [None for i in range(self.N)]
        self.heap_index = [None for i in range(self.N)]
        self.total = 0

    def push(self, idx, key):
        if idx >= self.N:
            raise IndexError('index is out of the range of IndexedMinPQ.')
        if self.key[idx] is not None:
            raise IndexError('index is already in the IndexedMinPQ.')

        self.total += 1
        self.key[idx] = key
        self.heap[self.total] = idx
        self.heap_index[idx] = self.total
        self.__swim(self.total)

    def __swim(self, i):
        parent_i = i//2

        while parent_i > 0:
            key = self.key[self.heap[i]]
            parent_key = self.key[self.heap[parent_i]]
            if parent_key < key:
                break
            self.heap[i], self.heap[parent_i] = self.heap[parent_i], self.heap[i]
            self.heap_index[self.heap[i]] , self.heap_index[self.heap[parent_i]] = \
                self.heap_index[self.heap[parent_i]], self.heap_index[self.heap[i]]

            i = parent_i
            parent_i = i//2

    def pop(self):
        if not self.is_empty():
            index = self.heap[1]
            out = self.key[self.heap[1]]
            self.key[self.heap[1]] = None
            self.heap_index[self.heap[1]] = None
            self.heap[1] = self.heap[self.total]
            self.heap_index[self.heap[1]] = 1
            self.heap[self.total] = None
            self.total -= 1
            self.__sink(1)
            return index, out
        raise IndexError('IndexedMinPQ is Empty')

    def __sink(self,i):
        child_i = i * 2
        if child_i <= self.total:
            key = self.key[self.heap[i]]
            child_key = self.key[self.heap[child_i]]
            other_child = child_i + 1
            if other_child <= self.total:
                other_child_key =  self.key[self.heap[other_child]]
                if other_child_key < child_key:
                    child_i = other_child
                    child_key = other_child_key
            if child_key < key:
                self.heap[i], self.heap[child_i] = self.heap[child_i], self.heap[i]
                self.heap_index[self.heap[i]], self.heap_index[self.heap[child_i]] = self.heap_index[self.heap[child_i]], self.heap_index[self.heap[i]]
                self.__sink(child_i)

    def is_empty(self):
        return self.total == 0

    def update(self, i, key):
        if key > self.key[i]:
            self.__increase_key(i, key)

        else:
            self.__decrease_key(i, key)


    def __decrease_key(self,i,key):
        if i<0 or i> self.N:
            raise IndexError('index i is not in the range')
        if self.key[i] is None:
            raise IndexError('index i is not in the IndexedMinPQ')
        assert type(i) is int
        assert key < self.key[i]
        self.key[i] = key
        self.__swim(self.heap_index[i])

    def __increase_key(self,i,key):
        if i<0 or i> self.N:
            raise IndexError('index i is not in the range')
        if self.key[i] is None:
            raise IndexError('index i is not in the IndexedMinPQ')
        assert type(i) is int
        assert key > self.key[i]
        self.key[i] = key
        self.__sink(self.heap_index[i])
