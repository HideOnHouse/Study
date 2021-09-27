#include "stdio.h"
#include "stdlib.h"

typedef struct vector {
    int *data;
    int size;
    int capacity;
} vector;

void push(vector *vector, int element) {
    if (vector->capacity < vector->size) {
        *(vector->data + vector->capacity) = element;
        vector->size++;
    } else {
        int *new_arr;
        if (vector->size == 0) {
            new_arr = malloc(sizeof(int));
            vector->capacity ++;
            vector->size = 1;
        } else {
            vector->capacity = vector->capacity * 2;
            new_arr = malloc(sizeof(int) * vector->capacity);
            for (int i = 0; i < vector->capacity; ++i) {
                *(new_arr + i) = *(vector->data + i);
            }
        }
        free(vector->data);
        vector->data = new_arr;
    }
}

int pop(vector *vector) {
    if (vector->size == 0) {
        printf("Can't pop element from empty vector\n");
        return (int) NULL;
    } else {
        int ret = *(vector->data + vector->size);
        free(vector->data + vector->size);
        vector->size--;
        vector->capacity--;
        return ret;
    }
}

void clear(vector *arr) {
    free(arr->data);
    arr->size = 0;
    arr->capacity = 0;
}

void print_all(const vector *arr) {
    for (int *i = arr->data; i < arr->data + arr->capacity; ++i) {
        printf("%d ", *i);
    }
    printf("\n");
}

int main() {
    vector v = {.size = 0, .capacity = 0};
    for (int i = 0; i < 10; ++i) {
        push(&v, i);
    }
    print_all(&v);
}