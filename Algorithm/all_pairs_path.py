def print_result(predecessor_matrix, i, j):
    if i == j:
        print(j, end=', ')
    elif predecessor_matrix[i][j] is None:
        print(f"No path from {i} to {j}")
    else:
        print_result(predecessor_matrix, i, predecessor_matrix[i][j])
        print(j, end=", ")


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


def main():
    weight_matrix = [[0, 3, 8, float('inf'), -4],
                     [float('inf'), 0, float('inf'), 1, 7],
                     [float('inf'), 4, 0, float('inf'), float('inf')],
                     [2, float('inf'), -5, 0, float('inf')],
                     [float('inf'), float('inf'), float('inf'), 6, 0]]
    result1 = slow_all_pairs_shortest_paths(weight_matrix)
    result2 = fast_all_pairs_shortest_paths(weight_matrix)
    result3, pi = floyd_warshall_algorithm(weight_matrix)
    assert result3 == result2 == result1
    print_result(pi, 4, 1)


if __name__ == '__main__':
    main()
