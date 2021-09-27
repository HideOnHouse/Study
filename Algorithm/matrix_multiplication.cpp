#include <iostream>
#include <random>

#define ARR_SIZE 2
using namespace std;


int **matmul(int **a, int **b) {
    static int **ret = new int *[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        ret[i] = new int[ARR_SIZE];
    }
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            int temp = 0;
            for (int k = 0; k < ARR_SIZE; ++k) {
                temp += a[i][k] * b[k][j];
            }
            ret[i][j] = temp;
        }
    }
    return ret;
}

int main() {
    int **arr1 = new int *[ARR_SIZE];
    int **arr2 = new int *[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        arr1[i] = new int[ARR_SIZE];
        arr2[i] = new int[ARR_SIZE];
    }
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> dist(-10, 10);

    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            arr1[i][j] = dist(generator);
            arr2[i][j] = dist(generator);
        }
    }

    int **arr3 = new int *[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        arr3[i] = new int[ARR_SIZE];
    }
    arr3 = matmul(arr1, arr2);
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            printf("%4d, ", arr3[i][j]);
        }
        cout << endl;
    }
    return 0;
}