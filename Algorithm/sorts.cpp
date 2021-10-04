#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>


namespace chrono = std::chrono;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

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

void insertion_sort(int *arr, int left, int right) {
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

void selection_sort(int *arr, int left, int right) {
    int *min;
    for (int *i = arr + left; i < arr + right; ++i) {
        min = i;
        for (int *j = i + 1; j < arr + right; ++j) {
            if (*min > *j) {
                min = j;
            }
        }
        swap(i, min);
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

void max_heapify(int *arr, int idx, int k) {
    int left_child;
    int right_child;
    int largest;
    while (true) {
        left_child = idx * 2 + 1;
        right_child = idx * 2 + 2;
        if (left_child < k and arr[idx] < arr[left_child]) {
            largest = left_child;
        } else {
            largest = idx;
        }
        if (right_child < k and arr[largest] < arr[right_child]) {
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

void heap_sort(int *arr, int left, int right) {
    int length = right - left + 1;
    int k = length;
    for (int idx = length / 2 - 1; idx >= 0; --idx) {
        max_heapify(arr, idx, k);
    }
    for (int i = length - 1; i >= 1; --i) {
        swap(arr + 0, arr + i);
        --k;
        max_heapify(arr, 0, k);
    }
}

void merge_sort(int *arr, int left, int right) {
    int *ret = new int[right - left + 1];
    merge_sort(arr, ret, left, right);
    delete[] ret;
}

int partition(int *arr, int left, int right) {
    int x = arr[right];
    int i = left - 1;
    for (int *j = arr + left; j < arr + right; ++j) {
        if (*j <= x) {
            ++i;
            swap(arr + i, j);
        }
    }
    swap(arr + i + 1, arr + right);
    return i + 1;
}

void quick_sort(int *arr, int left, int right) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        quick_sort(arr, left, pivot - 1);
        quick_sort(arr, pivot + 1, right);
    }
}

void counting_sort(int *arr, int left, int right, int k) {
    int *counter = new int[k + 1];
    int *temp = new int[right - left + 1];
    for (int i = 0; i <= k; ++i) {
        counter[i] = 0;
    }
    for (int i = left; i <= right; ++i) {
        ++counter[arr[i]];
    }
    for (int i = 1; i <= k; ++i) {
        counter[i] = counter[i] + counter[i - 1];
    }
    for (int i = right; i >= left; --i) {
        temp[counter[arr[i]] - 1] = arr[i];
        --counter[arr[i]];
    }
    for (int i = left; i <= right; ++i) {
        arr[i] = temp[i - left];
    }
    delete[] counter;
    delete[] temp;
}

void radix_sort(int *arr, int left, int right, int d) {
    int counter[16];
    int *temp = new int[right - left + 1];
    int key;
    for (int digit = 0; digit <= d; ++digit) {
        for (int &i: counter) {
            i = 0;
        }
        for (int *i = arr + left; i <= arr + right; ++i) {
            key = (*i >> digit * 4) & 0xf;
            ++counter[key];
        }
        for (int *i = counter + 1; i < counter + 16; ++i) {
            *i = *i + *(i - 1);
        }
        for (int *i = arr + right; i >= arr + left; --i) {
            key = (*i >> digit * 4) & 0xf;
            temp[counter[key] - 1] = *i;
            --counter[key];
        }
        for (int i = left; i <= right; ++i) {
            arr[i] = temp[i - left];
        }
    }
    delete[] temp;
}

void check_time(int *arr, int length, const std::string &s) {
    std::cout << "========== " << s << " Sort ==========" << std::endl;
    if (s == "bubble" and length <= 100000) {
        std::shuffle(arr, arr + length, std::default_random_engine(5)); // NOLINT(cert-msc51-cpp)
        print_all(arr, length);
        auto start = chrono::high_resolution_clock::now();
        bubble_sort(arr, 0, length - 1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        std::cout << "Execution Time : " << duration.count() << std::endl;
    } else if (s == "insertion" and length <= 100000) {
        std::shuffle(arr, arr + length, std::default_random_engine(5)); // NOLINT(cert-msc51-cpp)
        print_all(arr, length);
        auto start = chrono::high_resolution_clock::now();
        insertion_sort(arr, 0, length - 1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        std::cout << "Execution Time : " << duration.count() << std::endl;
    } else if (s == "selection" and length <= 100000) {
        std::shuffle(arr, arr + length, std::default_random_engine(5)); // NOLINT(cert-msc51-cpp)
        print_all(arr, length);
        auto start = chrono::high_resolution_clock::now();
        selection_sort(arr, 0, length - 1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        std::cout << "Execution Time : " << duration.count() << std::endl;
    } else if (s == "merge") {
        std::shuffle(arr, arr + length, std::default_random_engine(5)); // NOLINT(cert-msc51-cpp)
        print_all(arr, length);
        auto start = chrono::high_resolution_clock::now();
        merge_sort(arr, 0, length - 1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        std::cout << "Execution Time : " << duration.count() << std::endl;
    } else if (s == "heap") {
        std::shuffle(arr, arr + length, std::default_random_engine(5)); // NOLINT(cert-msc51-cpp)
        print_all(arr, length);
        auto start = chrono::high_resolution_clock::now();
        heap_sort(arr, 0, length - 1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        std::cout << "Execution Time : " << duration.count() << std::endl;
    } else if (s == "quick") {
        std::shuffle(arr, arr + length, std::default_random_engine(5)); // NOLINT(cert-msc51-cpp)
        print_all(arr, length);
        auto start = chrono::high_resolution_clock::now();
        quick_sort(arr, 0, length - 1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        std::cout << "Execution Time : " << duration.count() << std::endl;
    } else if (s == "counting") {
        std::shuffle(arr, arr + length, std::default_random_engine(5)); // NOLINT(cert-msc51-cpp)
        print_all(arr, length);
        auto start = chrono::high_resolution_clock::now();
        counting_sort(arr, 0, length - 1, length - 1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        std::cout << "Execution Time : " << duration.count() << std::endl;
    } else if (s == "radix") {
        std::shuffle(arr, arr + length, std::default_random_engine(5)); // NOLINT(cert-msc51-cpp)
        print_all(arr, length);
        auto start = chrono::high_resolution_clock::now();
        radix_sort(arr, 0, length - 1, static_cast<int>(log2(length) / 4));
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        std::cout << "Execution Time : " << duration.count() << std::endl;
    }
    print_all(arr, length);
}

int main(int argc, char *argv[]) {
    int arr_size;
    if (argc != 2) {
        std::cout << "Input array size\n>>> ";
        std::cin >> arr_size;
    } else {
        arr_size = strtol(argv[1], nullptr, 10);
    }
    int *arr = new int[arr_size];
    int length = arr_size;
    for (int i = 0; i < arr_size; ++i) {
        arr[i] = i;
    }
    std::cout << "ARRAY SIZE - " << arr_size << std::endl;
    check_time(arr, length, "bubble");
    check_time(arr, length, "insertion");
    check_time(arr, length, "selection");
    check_time(arr, length, "merge");
    check_time(arr, length, "heap");
    check_time(arr, length, "quick");
    check_time(arr, length, "counting");
    check_time(arr, length, "radix");
    return 0;
}