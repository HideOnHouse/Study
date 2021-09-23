#include <iostream>
#include <random>

using namespace std;

void matmul(int a[], int b[]) {

}

void fast_matmul(int a[], int b[]) {

}

void faster_matmul(int a[], int b[]) {

}

void fastest_matmul(int a[], int b[]) {

}

int main() {
    int (*arr)[10];
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> dist(-10, 10);

    for (int **i = arr; i < arr + sizeof(arr) * sizeof(arr[0]) * sizeof(int); ++i) {
        **i = dist(generator);
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}