#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

#define ARR_SIZE 100000

namespace chrono = std::chrono;

void print_all(const int *arr, size_t length) {
    if (length <= 100) {
    for (const int *i = arr; i < arr + length; ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    }
}

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
    int ret[right - left + 1];
    merge_sort(arr, ret, left, right);
}

void counting_sort(int *a, int left, int right, int k) {
    int counter[k + 1];
    int temp[right - left + 1];
    for (int i = 0; i <= k; ++i) {
        counter[i] = 0;
    }
    for (int i = left; i <= right; ++i) {
        ++counter[a[i]];
    }
    for (int i = 1; i <= k; ++i) {
        counter[i] = counter[i] + counter[i - 1];
    }
    for (int i = right; i >= left; --i) {
        temp[counter[a[i]] - 1] = a[i];
        --counter[a[i]];
    }
    for (int i = left; i <= right; ++i) {
        a[i] = temp[i - left];
    }
}

int main() {
    int arr[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        arr[i] = i;
    }
    int length = ARR_SIZE;
    std::cout << "Bubble Sort" << std::endl;
    std::shuffle(arr, arr + 9, std::default_random_engine(1)); // NOLINT(cert-msc51-cpp)
    print_all(arr, length);
    auto start = chrono::high_resolution_clock::now();
//    bubble_sort(arr, 0, length - 1);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    std::cout << "Execution Time : " << duration.count() << std::endl;
    print_all(arr, length);

    std::cout << "Insertion Sort" << std::endl;
    std::shuffle(arr, arr + 9, std::default_random_engine(2)); // NOLINT(cert-msc51-cpp)
    print_all(arr, length);
    start = chrono::high_resolution_clock::now();
    insertion_sort(arr, 0, length - 1);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    std::cout << "Execution Time : " << duration.count() << std::endl;
    print_all(arr, length);

    std::cout << "Merge Sort" << std::endl;
    std::shuffle(arr, arr + 9, std::default_random_engine(3)); // NOLINT(cert-msc51-cpp)
    print_all(arr, length);
    start = chrono::high_resolution_clock::now();
    merge_sort(arr, 0, length - 1);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    std::cout << "Execution Time : " << duration.count() << std::endl;
    print_all(arr, length);

    std::cout << "Counting Sort" << std::endl;
    print_all(arr, length);
    start = chrono::high_resolution_clock::now();
    counting_sort(arr, 0, length - 1, ARR_SIZE);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    std::cout << "Execution Time : " << duration.count() << std::endl;
    print_all(arr, length);
    return 0;
}