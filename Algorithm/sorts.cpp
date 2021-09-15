#include <iostream>
#include <algorithm>
#include <random>


void bubble_sort(int *arr, int left, int right) {
    int temp;
    for (int i = left; i < right; ++i) {
        for (int j = i; j < right; ++j) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void insertion_sort(int arr[], int left, int right) {
    int key, j;
    for (int i = left + 1; i < right; ++i) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


void merge(int *arr, int *ret, const int left, const int right) {
    int mid = (left + right) / 2;
    int first_idx = left;
    int second_idx = mid + 1;
    int idx = left;

    // merge
    while (first_idx <= mid && second_idx <= right) {
        if (arr[first_idx] <= arr[second_idx]) {
            ret[idx] = arr[first_idx];
            first_idx++;
        } else {
            ret[idx] = arr[second_idx];
            second_idx++;
        }
        idx++;
    }

    // handle remains
    while (first_idx <= mid) {
        ret[idx] = arr[first_idx];
        idx++;
        first_idx++;
    }

    while (second_idx <= right) {
        ret[idx] = arr[second_idx];
        idx++;
        second_idx++;
    }

    // copy array
    for (int i = left; i <= right; ++i) {
        arr[i] = ret[i];
    }
}

void merge_sort(int *arr, int *ret, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, ret, left, mid);
        merge_sort(arr, ret, mid + 1, right);
        merge(arr, ret, left, right);
    }
}

void merge_sort(int *arr, int left, int right) {
    int ret[] = {0, 0, 0, 0, 0, 0, 0, 0 ,0};
    merge_sort(arr, ret, left, right);
}

int main() {
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::shuffle(arr, arr + 9, std::default_random_engine(1)); // NOLINT(cert-msc51-cpp)
    for (int *i = arr; i < arr + sizeof(arr) / sizeof(int); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    bubble_sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
    for (int *i = arr; i < arr + sizeof(arr) / sizeof(int); ++i) {
        std::cout << *i << " ";
    }


    std::cout << '\n' << std::endl;

    std::shuffle(arr, arr + 9, std::default_random_engine(2)); // NOLINT(cert-msc51-cpp)
    for (int *i = arr; i < arr + sizeof(arr) / sizeof(int); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    insertion_sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
    for (int *i = arr; i < arr + sizeof(arr) / sizeof(int); ++i) {
        std::cout << *i << " ";
    }
    std::cout << '\n' << std::endl;

    std::shuffle(arr, arr + 9, std::default_random_engine(1)); // NOLINT(cert-msc51-cpp)
    for (int *i = arr; i < arr + sizeof(arr) / sizeof(int); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    merge_sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
    for (int *i = arr; i < arr + sizeof(arr) / sizeof(int); ++i) {
        std::cout << *i << " ";
    }
    std::cout << '\n' << std::endl;
    return 0;
}