#include "stdio.h"

float fractional_knapsack(const float *weights, const int *values, int n, float capacity) {
    // Sort First!
    float ret = 0;
    float load = 0;
    int idx = 0;
    while (load < capacity && idx < n) {
        if (weights[idx] <= capacity - load) {
            capacity -= load;
        } else {
            capacity -= (capacity - load) / weights[idx];
        }
        idx += 1;
    }
    return ret;
}

int main() {
    int w[] = {10, 20, 30};
    int v[] = {60, 100, 120};
    float result = fractional_knapsack(w, v, sizeof(w) / sizeof(int), 50);
    printf("%f\n", result);
    return 0;
}
