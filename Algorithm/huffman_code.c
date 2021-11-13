#include "stdio.h"

typedef struct node {
    void *left;
    void *right;
    int freq;
} node;

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(int *arr, int idx, int k) {
    int left_child;
    int right_child;
    int largest;
    while (1) {
        left_child = idx * 2 + 1;
        right_child = idx * 2 + 2;
        if (left_child < k && arr[idx] < arr[left_child]) {
            largest = left_child;
        } else {
            largest = idx;
        }
        if (right_child < k && arr[largest] < arr[right_child]) {
            largest = right_child;
        }
        if (largest != idx) {
            swap(arr + idx, arr + largest);
            idx = largest;
        } else {
            break;
        }
    }
}

void huffman(char *c) {

}

int main() {
    return 0;
}