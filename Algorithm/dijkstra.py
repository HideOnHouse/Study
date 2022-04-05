import heapq
from pprint import pprint


def dijkstra(graph: dict, source):
    # Single Source Initialization
    distances = {vertex: float('inf') for vertex in graph}
    distances[source] = 0
    queue = []
    heapq.heappush(queue, [distances[source], source])

    while queue:
        cur_d, cur_pi = heapq.heappop(queue)  # Extract_min
        if distances[cur_pi] >= cur_d:
            for pi, d in graph[cur_pi].items():  # For v in G.Adj[u]
                # Relax(u, v, weight)
                dist = cur_d + d
                if dist < distances[pi]:
                    distances[pi] = dist
                    heapq.heappush(queue, [dist, pi])
                # end Relax
    return distances


def main():
    num_village = 5
    road = [[1, 2, 1], [2, 3, 3], [5, 2, 2], [1, 4, 2], [5, 3, 1], [5, 4, 2]]
    max_time = 3

    # parsing weights
    graph = dict()
    for i in road:
        u, v, weight = i
        if u in graph:
            if v in graph[u]:
                graph[u][v] = min(weight, graph[u][v])
            else:
                graph[u][v] = weight
        else:
            graph[u] = {
                v: weight
            }
        u, v = v, u
        if u in graph:
            if v in graph[u]:
                graph[u][v] = min(weight, graph[u][v])
            else:
                graph[u][v] = weight
        else:
            graph[u] = {
                v: weight
            }
    result = dijkstra(graph, 1)
    print(result)


if __name__ == '__main__':
    main()
