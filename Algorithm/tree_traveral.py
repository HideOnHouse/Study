class Node:
    def __init__(self, value, adg: list = None):
        self.value = value
        self.adj = adg

    def get_adj(self):
        return self.adj


def BFS(tree: Node):
    visited = set()

    visited.add(tree)
    queue = [tree]

    while len(queue) != 0:
        head = queue.pop(0)
        print(head.value, end=" ")
        for adj in head.get_adj():
            if adj not in visited:
                visited.add(adj)
                queue.append(adj)
    print()


def DFS(tree: Node):
    visited = set()


def main():
    root = Node(1)


if __name__ == '__main__':
    main()
