def max_heapify(arr: list, idx: int, length: int):
    left = idx * 2 + 1
    right = idx * 2 + 2
    if left < length and arr[idx] < arr[left]:
        largest = left
    else:
        largest = idx
    if right < length and arr[largest] < arr[right]:
        largest = right
    if largest != idx:
        arr[idx], arr[largest] = arr[largest], arr[idx]
        max_heapify(arr, largest, length)


def build_max_heap(arr: list, length: int):
    for i in range(length // 2, -1, -1):
        max_heapify(arr, i, length)


def heap_sort(arr: list, length: int, k: int):
    build_max_heap(arr, length)
    for i in range(length - 1, k, -1):
        arr[i], arr[0] = arr[0], arr[i]
        length -= 1
        max_heapify(arr, 0, length)


def solution(arr: list, k: int = 0):
    heap_sort(arr, len(arr), k)


def main():
    arr = [*range(100, -1, -1)]
    print(arr)
    solution(arr)
    print(arr)


if __name__ == '__main__':
    main()
