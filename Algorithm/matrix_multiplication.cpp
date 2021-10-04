#include <iostream>
#include <random>

#define arr_size 2
using namespace std;


int **matmul(int **a, int **b) {
    static int **ret = new int *[arr_size];
    for (int i = 0; i < arr_size; ++i) {
        ret[i] = new int[arr_size];
    }
    for (int i = 0; i < arr_size; ++i) {
        for (int j = 0; j < arr_size; ++j) {
            int temp = 0;
            for (int k = 0; k < arr_size; ++k) {
                temp += a[i][k] * b[k][j];
            }
            ret[i][j] = temp;
        }
    }
    return ret;
}

int main() {
    int **arr1 = new int *[arr_size];
    int **arr2 = new int *[arr_size];
    for (int i = 0; i < arr_size; ++i) {
        arr1[i] = new int[arr_size];
        arr2[i] = new int[arr_size];
    }
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> dist(-10, 10);

    for (int i = 0; i < arr_size; ++i) {
        for (int j = 0; j < arr_size; ++j) {
            arr1[i][j] = dist(generator);
            arr2[i][j] = dist(generator);
        }
    }

    int **arr3 = new int *[arr_size];
    for (int i = 0; i < arr_size; ++i) {
        arr3[i] = new int[arr_size];
    }
    arr3 = matmul(arr1, arr2);
    for (int i = 0; i < arr_size; ++i) {
        for (int j = 0; j < arr_size; ++j) {
            printf("%4d, ", arr3[i][j]);
        }
        cout << endl;
    }
    return 0;
}