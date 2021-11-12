#include "stdio.h"
#include "string.h"

#define max(x, y) ((x) > (y) ? (x) : (y))

/*
 * F(s1[:i], s2[:i]) = 1 + F(s1[:i-1], s2[:i-1]) if s1[i] = s2[i]
 */
int lcs_(char *s1, char *s2, int (*dp)[101]) {
    int l1 = (int) strlen(s1);
    int l2 = (int) strlen(s2);
    for (int i = 1; i <= l1; ++i) {
        for (int j = 1; j <= l2; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }
    return dp[l1][l2];
}


int lcs(char *str1, char *str2) {
    int ret;
    int dp[101][101];
    for (int i = 0; i < 101; ++i) {
        dp[0][i] = 0;
        dp[i][0] = 0;
    }
    ret = lcs_(str1, str2, dp);
    return ret;
}

int main() {
    int num_case;
    char str1[101];
    char str2[101];
    scanf("%d", &num_case);
    for (int i = 0; i < num_case; ++i) {
        scanf("%s %s", str1, str2);
        printf("%d\n", lcs(str1, str2));
    }
    return 0;
}
