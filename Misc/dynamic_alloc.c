#include "stdio.h"
#include "stdlib.h"

typedef struct vector {
    int *data;
    int size;
    int capacity;
} vector;

void push(vector *list, int element) {
    if (list->capacity < list->size) {
        *(list->data + list->capacity) = element;
        list->capacity++;
    } else {
        int *new_arr;
        if (list->size == 0) {
            new_arr = malloc(sizeof(int));
            list->size = 1;
        } else {
            new_arr = malloc(sizeof(int) * list->size * 2);
            list->size = list->size * 2;
            for (int i = 0; i < list->capacity; ++i) {
                *(new_arr + i) = *(list->data + i);
            }
        }
        free(list->data);
        list->data = new_arr;
        push(list, element);
    }
}

void pop(vector arr, int element) {

}

void clear(vector *arr) {
    free(arr->data);
    arr->size = 0;
    arr->capacity = 0;
}

void print_all(vector list) {
    for (int *i = list.data; i < list.data + list.capacity; ++i) {
        printf("%d ", *i);
    }
    printf("\n");
}

int main() {
    vector array = {.data = malloc(sizeof(int) * 100000000), .size = 0, .capacity = 0};
    for (int i = 0; i < 100000000; ++i) {
        push(&array, i);
    }
//    print_all(array);
    return 0;
}