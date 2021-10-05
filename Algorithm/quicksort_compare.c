#include "stdio.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition_hoare(int *arr, int left, int right, int *swp, int *cmp) {
    int pivot = arr[left];
    int i = left - 1;
    int j = right + 1;
    while (1) {
        do {
            ++*cmp;
            ++i;
        } while (arr[i] < pivot);
        do {
            ++*cmp;
            --j;
        } while (arr[j] > pivot);
        if (i < j) {
            swap(arr + i, arr + j);
            ++*swp;
        } else {
            return j;
        }
    }
}

void hoare(int *arr, int left, int right, int *swp, int *cmp) {
    if (left < right) {
        int p = partition_hoare(arr, left, right, swp, cmp);
        hoare(arr, left, p, swp, cmp);
        hoare(arr, p + 1, right, swp, cmp);
    }
}

int partition_lomuto(int *arr, int left, int right, int *swp, int *cmp) {
    int pivot = arr[left];
    int j = left;
    for (int *i = arr + left + 1; i <= arr + right; ++i) {
        ++*cmp;
        if (*i < pivot) {
            ++j;
            swap(i, arr + j);
            ++*swp;
        }
    }
    swap(arr + j, arr + left);
    ++*swp;
    return j;
}

void lomuto(int *arr, int left, int right, int *swp, int *cmp) {
    if (left < right) {
        int p = partition_lomuto(arr, left, right, swp, cmp);
        lomuto(arr, left, p - 1, swp, cmp);
        lomuto(arr, p + 1, right, swp, cmp);
    }
}

int main() {
    int num, n;
    scanf("%d", &num);
    for (int i = 0; i < num; ++i) {
        int a = 0, b = 0, c = 0, d = 0;
        scanf("%d", &n);
        int arr1[n];
        int arr2[n];
        for (int j = 0; j < n; ++j) {
            scanf("%d", arr1 + j);
            *(arr2 + j) = *(arr1 + j);
        }
        hoare(arr1, 0, n - 1, &a, &b);
        lomuto(arr2, 0, n - 1, &c, &d);
        printf("%d %d %d %d\n", a, c, b, d);
    }
    return 0;
}