#include "stdlib.h"
#include "stdio.h"

/**
 * parent i
 * left child i * 2 + 1
 * right child i * 2 + 2
 */

typedef struct heap {
    int *arr;
    int size;
    int capacity;
} heap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(heap *heap, int idx) {
    int left_child = idx * 2 + 1;
    int right_child = idx * 2 + 2;
    int largest;
    if (left_child < heap->size && heap->arr[left_child] > heap->arr[idx]) {
        largest = left_child;
    } else {
        largest = idx;
    }
    if (right_child < heap->size && heap->arr[right_child] > heap->arr[largest]) {
        largest = right_child;
    }
    if (largest != idx) {
        swap(&heap->arr[idx], &heap->arr[largest]);
        max_heapify(heap, largest);
    }
}

void build_max_heap(heap *heap) {
    for (int i = heap->size / 2; i >= 0; --i) {
        max_heapify(heap, i);
    }
}

void heap_sort(heap *heap) {
    int length = heap->size;
    for (int i = length - 1; i >= 1; --i) {
        swap(&heap->arr[0], &heap->arr[i]);
        heap->size--;
        max_heapify(heap, 0);
    }
    heap->size = length;
}


int main() {
    heap h = {.arr = malloc(sizeof(int) * 10), .size = 0, .capacity = 10};
    for (int i = 0; i < 10; ++i) {
        h.arr[i] = i;
        h.size++;
        printf("%d ", h.arr[i]);
    }
    printf("\n");
    build_max_heap(&h);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", h.arr[i]);
    }
    printf("\n");
    heap_sort(&h);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", h.arr[i]);
    }
    printf("\n");
}