#include "stdio.h"

typedef struct heap {
    int *arr;
    int size;
} heap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_push(heap *heap, int value) {
    int *arr = heap->arr;
    int size = heap->size;
    arr[size] = value;
    int current = size;
    int parent = (size - 1) / 2;

    while (current > 0 && arr[current] > arr[parent]) {
        swap(arr + current, arr + parent);
        current = parent;
        parent = (parent - 1) / 2;
    }

    ++heap->size;
}


int max_pop(heap *heap) {
    int *arr = heap->arr;
    int size = heap->size;
    int ret = arr[0];
    int left_child;
    int right_child;
    int largest;
    int idx = 0;

    --size;
    arr[0] = arr[size];

    while (1) {
        left_child = idx * 2 + 1;
        right_child = idx * 2 + 2;
        if (left_child < size && arr[idx] < arr[left_child]) {
            largest = left_child;
        } else {
            largest = idx;
        }
        if (right_child < size && arr[largest] < arr[right_child]) {
            largest = right_child;
        }
        if (largest != idx) {
            swap(arr + idx, arr + largest);
            idx = largest;
        } else {
            break;
        }
    }

    --heap->size;
    return ret;
}

void min_push(heap *heap, int value) {
    int *arr = heap->arr;
    int size = heap->size;
    arr[size] = value;
    int current = size;
    int parent = (size - 1) / 2;

    while (current > 0 && arr[current] < arr[parent]) {
        swap(arr + current, arr + parent);
        current = parent;
        parent = (parent - 1) / 2;
    }

    ++heap->size;
}


int min_pop(heap *heap) {
    int *arr = heap->arr;
    int size = heap->size;
    int ret = arr[0];
    int left_child;
    int right_child;
    int smallest;
    int idx = 0;

    --size;
    arr[0] = arr[size];

    while (1) {
        left_child = idx * 2 + 1;
        right_child = idx * 2 + 2;
        if (left_child < size && arr[idx] > arr[left_child]) {
            smallest = left_child;
        } else {
            smallest = idx;
        }
        if (right_child < size && arr[smallest] > arr[right_child]) {
            smallest = right_child;
        }
        if (smallest != idx) {
            swap(arr + idx, arr + smallest);
            idx = smallest;
        } else {
            break;
        }
    }
    --heap->size;
    return ret;
}

void push(heap *max_heap, heap *min_heap, int value) {
    if (max_heap->size == min_heap->size) {
        max_push(max_heap, value);
        min_push(min_heap, max_pop(max_heap));
    } else {
        min_push(min_heap, value);
        max_push(max_heap, min_pop(min_heap));
    }
}

int get_median(heap *max_heap, heap *min_heap) {
    int ret;
    if (max_heap->size == min_heap->size) {
        ret = (min_heap->arr[0] + max_heap->arr[0]) / 2;
    } else if (max_heap->size > min_heap->size) {
        ret = max_heap->arr[0];
    } else {
        ret = min_heap->arr[0];
    }
    return ret;
}

int main() {
    int num_case, num_count;
    scanf("%d", &num_case);
    for (int i = 0; i < num_case; ++i) {
        int answer = 0;
        scanf("%d", &num_count);
        int max_arr[num_count];
        int min_arr[num_count];
        int value;
        heap max_heap = {.arr = max_arr, .size = 0};
        heap min_heap = {.arr = min_arr, .size = 0};
        for (int j = 0; j < num_count; ++j) {
            scanf("%d", &value);
            push(&max_heap, &min_heap, value);
            answer += get_median(&max_heap, &min_heap) % 10;
        }
        printf("%d\n", answer % 10);
    }
    return 0;
}
