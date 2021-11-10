#include "stdio.h"

int greedy_activity_selector(const int *start_times, const int *finish_times, int n) {
    int ret = 1;
    int k = 0;
    for (int m = 1; m < n; ++m) {
        if (start_times[m] >= finish_times[k]) {
            ++ret;
            k = m;
        }
    }
    return ret;
}

int main() {
    int s[] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int f[] = {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    int result = greedy_activity_selector(s, f, sizeof(s) / sizeof(int));
    printf("%d\n", result);
    return 0;
}