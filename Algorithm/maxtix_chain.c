#include "limits.h"
#include "stdio.h"

int matrix_chain(int num_matrix, const int *p) {
    // p[0] x p[1], p[1] x p[2], p[2] x p[3] ...
    int n = num_matrix;
    int m[n + 1][n + 1];
    for (int i = 1; i <= n; ++i) {
        m[i][i] = 0;
    }
    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; ++k) {
                int q = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j]);
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        }
    }
    return m[1][n];
}

int main() {
    int num_case;
    scanf("%d", &num_case);
    for (int i = 0; i < num_case; ++i) {
        int num_matrix;
        scanf("%d", &num_matrix);
        int p[num_matrix + 1];
        for (int *j = p; j <= p + num_matrix; ++j) {
            scanf("%d", j);
        }
        printf("%d\n", matrix_chain(num_matrix, p));
    }
    return 0;
}
