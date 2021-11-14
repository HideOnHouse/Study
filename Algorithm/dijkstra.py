class Vertex:
    def __init__(self, distance=4294967295, pi=None):
        self.distance = distance
        self.pi = pi


def relax(u: Vertex, v: Vertex, weight: int):
    temp = u.distance + weight
    if v.distance > temp:
        v.distance = temp
        v.pi = v


def extract_min(queue) -> Vertex:
    pass


def main():
    num_village = 5
    road = [[1, 2, 1], [2, 3, 3], [5, 2, 2], [1, 4, 2], [5, 3, 1], [5, 4, 2]]
    max_time = 3

    # initialize single source
    graph = [Vertex()] * num_village
    graph[0].distance = 0

    # initialize S and Q
    stack = []
    queue = graph

    while queue:
        u = extract_min(queue)
        stack.append(u)
        # for v in G.Adh[u]
        # relax(u, v, w)


if __name__ == '__main__':
    main()
