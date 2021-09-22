#include <iostream>
#include <climits>
#include <random>

int find_maximum_crossing_subarray(const int arr[], int left, int mid, int right) {
    int left_sum = INT_MIN;
    int temp = 0;
    for (int i = mid; i >= left; --i) {
        temp += arr[i];
        if (temp > left_sum) {
            left_sum = temp;
        }
    }
    temp = 0;
    int right_sum = INT_MIN;
    for (int i = mid + 1; i <= right; ++i) {
        temp += arr[i];
        if (temp > right_sum) {
            right_sum = temp;
        }
    }
    int max_sum = left_sum + right_sum;
    return max_sum;
}

int find_maximum_subarray(int arr[], int left, int right) {
    if (left == right) {
        return arr[left];
    } else {
        int mid = (left + right) / 2;
        int left_sum = find_maximum_subarray(arr, left, mid);
        int mid_sum = find_maximum_crossing_subarray(arr, left, mid, right);
        int right_sum = find_maximum_subarray(arr, mid + 1, right);
        return std::max(std::max(left_sum, mid_sum), right_sum);
    }
}

int main() {
    int arr[10];
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> dist(-10, 10);
    for (int &i : arr) {
        i = dist(generator);
    }
    for (const auto &item : arr) {
        std::cout << " " << item;
    }
    int answer = find_maximum_subarray(arr, 0, sizeof(arr) / sizeof(int) - 1);
    std::cout << '\n' << answer << std::endl;
    return 0;
}