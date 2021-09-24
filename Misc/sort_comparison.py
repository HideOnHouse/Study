from matplotlib import pyplot as plt
import random
import time

from tqdm import tqdm


def bubble_sort(arr, begin, end):
    for i in range(begin, end + 1):
        for j in range(i, end + 1):
            if arr[i] > arr[j]:
                temp = arr[i]
                arr[i] = arr[j]
                arr[j] = temp


def insertion_sort(arr, begin, end):
    for i in range(begin + 1, end + 1):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key


def merge(arr, begin, end, ret):
    mid = (begin + end) // 2
    idx, left_idx, right_idx = begin, begin, mid + 1
    while left_idx <= mid and right_idx <= end:
        if arr[left_idx] <= arr[right_idx]:
            ret[idx] = arr[left_idx]
            left_idx += 1
        else:
            ret[idx] = arr[right_idx]
            right_idx += 1
        idx += 1

    while left_idx <= mid:
        ret[idx] = arr[left_idx]
        left_idx += 1
        idx += 1
    while right_idx <= end:
        ret[idx] = arr[right_idx]
        right_idx += 1
        idx += 1

    for i in range(begin, end + 1):
        arr[i] = ret[i]


def merge_sort(arr, begin, end, ret=None):
    if ret is None:
        ret = arr[::]
    if begin < end:
        mid = (begin + end) // 2
        merge_sort(arr, begin, mid, ret)
        merge_sort(arr, mid + 1, end, ret)
        merge(arr, begin, end, ret)


def main():
    result = [[], [], []]
    for i in tqdm((range(0, 10000, 100))):
        array = [*range(i)]
        for idx, sort in enumerate([bubble_sort, insertion_sort, merge_sort]):
            random.shuffle(array)
            start = time.time()
            sort(array, 0, len(array) - 1)
            end = time.time()
            result[idx].append(end - start)
    plt.figure(figsize=(16, 9))
    plt.plot(result[0], label='Bubble Sort')
    plt.plot(result[1], label='Insertion Sort')
    plt.plot(result[2], label='Merge sort')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    main()
