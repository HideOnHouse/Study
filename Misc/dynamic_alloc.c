#include "stdio.h"
#include "stdlib.h"

typedef struct vector {
    int *arr;
    int max_len;
    int current_len;
} vector;

void push(vector *list, int element) {
    if (list->current_len < list->max_len) {
        *(list->arr + list->current_len) = element;
        list->current_len++;
    } else {
        int *new_arr;
        if (list->max_len == 0) {
            new_arr = malloc(sizeof(int));
            list->max_len = 1;
        } else {
            new_arr = malloc(sizeof(int) * list->max_len * 2);
            list->max_len = list->max_len * 2;
            for (int i = 0; i < list->current_len; ++i) {
                *(new_arr + i) = *(list->arr + i);
            }
        }
        free(list->arr);
        list->arr = new_arr;
        push(list, element);
    }
}

void pop(vector arr, int element) {

}

void clear(vector arr, int element) {

}

void print_all(vector list) {
    for (int *i = list.arr; i < list.arr + list.current_len; ++i) {
        printf("%d ", *i);
    }
    printf("\n");
}

int main() {
    vector array = {.max_len = 0, .current_len = 0};
    for (int i = 0; i < 100000000; ++i) {
        push(&array, i);
    }
//    print_all(array);
    return 0;
}