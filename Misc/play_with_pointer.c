#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

void print_all(int *arr) {
    for (int *i = arr; i < arr + _msize(arr) / sizeof(int); ++i) {
        printf("%d ", *i);
    }
    printf("\n");
}

int main() {
    // malloc and pointer
    int *a;
    a = malloc(sizeof(int));
    *a = 12345;
    printf("%d\n", *a);
    free(a);
    int *arr;
    arr = malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; ++i) {
        *(arr + i) = i;
    }
    print_all(arr);
    int **double_arr;
    double_arr = malloc(sizeof(int *) * 10);
    for (int **i = double_arr; i < double_arr + 10; ++i) {
        i = malloc(sizeof(int) * 10);
        for (int j = 0; j < 10; ++j) {
            *(*i + j) = 10 - j;
        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%d ", *(*(double_arr + i) + j));
        }
        printf("\n");
    }
    return 0;
}