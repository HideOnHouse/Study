#include "stdio.h"
#include "limits.h"

int main() {
    int num_case, total_change, num_coin;
    scanf("%d", &num_case);
    for (int i = 0; i < num_case; ++i) {
        scanf("%d", &total_change);
        scanf("%d", &num_coin);
        int coins[num_coin];
        int dp[total_change + 1];
        dp[0] = 0;
        for (int j = 1; j <= total_change; ++j) {
            dp[j] = INT_MAX;
        }
        for (int j = 0; j < num_coin; ++j) {
            scanf("%d", coins + j);
        }
        for (int j = 0; j < num_coin; ++j) {
            int temp;
            for (int k = coins[j]; k <= total_change; ++k) {
                temp = dp[k - coins[j]] + 1;
                if (temp < dp[k]) {
                    dp[k] = temp;
                }
            }
        }
        printf("%d\n", dp[total_change]);
    }
    return 0;
}