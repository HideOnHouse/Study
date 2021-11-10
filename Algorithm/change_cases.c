#include "stdio.h"
#include "stdlib.h"

int cmp(const void *a, const void *b) {
    int n1 = *(int *) a;
    int n2 = *(int *) b;
    if (n1 < n2) {
        return -1;
    } else if (n1 > n2) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int num_case, total_change, num_coin;
    scanf("%d", &num_case);
    for (int i = 0; i < num_case; ++i) {
        scanf("%d", &total_change);
        scanf("%d", &num_coin);
        int coins[num_coin];
        int dp[total_change + 1];
        for (int j = 0; j <= total_change; ++j) {
            dp[j] = 0;
        }
        for (int j = 0; j < num_coin; ++j) {
            scanf("%d", coins + j);
        }
        qsort(coins, sizeof(coins) / sizeof(int), sizeof(int), cmp);
        for (int j = 0; j < num_coin; ++j) {
            for (int k = 1; k <= total_change; ++k) {
                if (coins[j] == k || coins[j] == 1) {
                    dp[k] += 1;
                } else if (k >= coins[j]) {
                    dp[k] = dp[k] + dp[k - coins[j]];
                }
            }
        }
        printf("%d\n", dp[total_change]);
    }
    return 0;
}
