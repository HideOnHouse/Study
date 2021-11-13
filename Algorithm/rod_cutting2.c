#include "stdio.h"
#include "limits.h"

/*
 * dp[left][right] = (right - left) + min(dp[left][i] + dp[i][right] i in slices)
 */
int rod_cutting_(int rod_length, int left, int right, int num_slices, int *slices, int (*dp)[rod_length]) {
    if (dp[left][right] != -1) {
        return dp[left][right];
    }
    int slice_left = num_slices;
    int slice_right = 0;
    for (int i = 0; i < num_slices; ++i) {
        if (left < slices[i] && slices[i] < right) {
            slice_left = i < slice_left ? i : slice_left;
            slice_right = i;
        }
    }
    if (slice_left == num_slices && slice_right == 0) {
        return 0;
    }

    int ret = INT_MAX;
    for (int i = slice_left; i <= slice_right; ++i) {
        int temp = (right - left) +
                   rod_cutting_(rod_length, left, slices[i], num_slices, slices, dp) +
                   rod_cutting_(rod_length, slices[i], right, num_slices, slices, dp);
        if (temp < ret) {
            ret = temp;
        }
    }
    dp[left][right] = ret;
    return ret;
}

int rod_cutting(int rod_length, int num_slice, int *slices) {
    int ret;
    int dp[rod_length + 1][rod_length + 1];
    for (int i = 0; i <= rod_length; ++i) {
        for (int j = 0; j <= rod_length; ++j) {
            dp[i][j] = -1;
        }
    }
    ret = rod_cutting_(rod_length, 0, rod_length, num_slice, slices, dp);
    return ret;
}

int main() {
    int num_case, rod_length, num_slice;
    scanf("%d", &num_case);
    for (int i = 0; i < num_case; ++i) {
        scanf("%d %d", &rod_length, &num_slice);
        int slices[num_slice];
        for (int *j = slices; j < slices + num_slice; ++j) {
            scanf("%d", j);
        }
        printf("%d\n", rod_cutting(rod_length, num_slice, slices));
    }
    return 0;
}
