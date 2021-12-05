# Graph
Abstract way of representing connectivity using nodes and edges
- Directed Graph
- Undirected Graph
# Tree
A connected acyclic graph
## Traversal of Tree
### BFS
1. Init each vertex except source
2. Mark source as discovered (not finished!)
3. Enqueue source
4. while queue is empty
   1. dequeue head
   2. for each adjust vertices
   3. make vertex as discovered
   4. enqueue vertex
   5. mark head as finished
### DFS
1. Init each vertex
2. set time as 0
3. for each vertex in graph
   1. if vertex is innocent
   2. DFS
- DFS
  1. ++ time
  2. make self.start as time
  3. make self.color as visited
  4. for each adjust vertex with self
     1. if vertex is innocent
     2. mark vertex.predecessor as self
     3. DFS v
  5. mark self as black
  6. ++time
  7. make self.finish as time
### Topological sort dag(directed acyclic graph) using DFS
  - DFS graph first
  - sort vertex as decreasing order of finished time
### Finding SCC(strongly connected components)
  1. DFS graph first
  2. DFS graph order of decreasing via finish time with transpose of graph
  3. Each generated forest is SCC
## Minimum Spanning Tree
  Connect all vertex with the smallest weight
### Kruskal's Algorithm
1. make set for each vertex
2. sort each edge into **non-decreasing** order via weight
3. for each edge
   1. if u.set is not same as v.set
   2. add edge to ret set
   3. union u.set and v.set
4. return ret set
### Prim's Algorithm
1. initialize all vertex (like dijkstra)
2. initialize source (like dijkstra)
3. enqueue all vertex to queue
4. while queue is empty
   1. extract_min head
   2. for each adjust vertex
      1. relax head, vertex
## Single Source Shortest Path
get all vertices shortest path from single source
### Bellman-Ford's Algorithm
1. Initialize single source
2. relax each edge for (number of vertices - 1)
3. check negative cycle
### Dijkstra's algorithm
1. Initialize single source
2. enqueue source
3. while queue is empty
    1. extract_min head (just pop from queue if graph is fully connected)
    2. for each adjust vertex
        1. relax head, vertex
## All pairs Shortest Path
### Single Source Short Path for each vertex
### Matrix Multiplication Method, Floyd-Warshall Algorithm
```python
def extend_shortest_path(l_m, w):
    n = len(l_m)
    l_prime = [[float('inf')] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                l_prime[i][j] = min(l_prime[i][j], l_m[i][k] + w[k][j])
    return l_prime

def slow_all_pairs_shortest_paths(w):
    n = len(w)
    ret = dict()
    ret[1] = w
    for m in range(2, n):
        ret[m] = [[0] * n for _ in range(n)]
        ret[m] = extend_shortest_path(ret[m - 1], w)
    return ret[n - 1]


def fast_all_pairs_shortest_paths(w):
    n = len(w)
    ret = dict()
    ret[1] = w
    m = 1
    while m < n - 1:
        ret[2 * m] = [[0] * n for _ in range(n)]
        ret[2 * m] = extend_shortest_path(ret[m], ret[m])
        m = 2 * m
    return ret[m]


def floyd_warshall_algorithm(w):
    n = len(w)
    distances = dict()
    distances[0] = w
    predecessor = dict()
    predecessor[0] = [[None if (i == j or w[i][j] == float('inf')) else i for j in range(n)] for i in range(n)]
    for k in range(1, n + 1):
        distances[k] = [[0] * n for _ in range(n)]
        predecessor[k] = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                temp = distances[k - 1][i][k - 1] + distances[k - 1][k - 1][j]
                if temp < distances[k - 1][i][j]:
                    distances[k][i][j] = temp
                    predecessor[k][i][j] = predecessor[k - 1][k - 1][j]
                else:
                    distances[k][i][j] = distances[k - 1][i][j]
                    predecessor[k][i][j] = predecessor[k - 1][i][j]
    return distances[n], predecessor[n]
```
## Max Flow
### Ford-Fulkerson Method
1. Initialize all flow to 0
2. while augmenting path is exists in residual network --> find augment using BFS
   1. augment flor f along p
3. return flow
### Matching
find maximum count of edge that makes all vertices is connected of incident of connected vertex
## String Matching
### Naive Algorithm (Brute Force) --> How to avoid backup?
### DFA(Deterministic Finite State Automata)
1. Make DFA
```c
int pat_len = strlen(pattern);
DFA[pattern[0]][0] = 1;
for (int X = 0, j = 1; j < pat_len; ++j) {
    // Duplicate State
    for (int c = 0; c < R; ++c) {
        DFA[c][j] = DFA[c][X];
    }
    // Update State
    DFA[pattern[j]][j] = ++j;
    X = DFA[pattern[j]][X];
}
```
2. move to state of DFA `j = DFA[text[i][j]`
3. match true if `j == length of pattern`  

**_Make transition of accept state to find all pattern matching count_**
### Fail Function