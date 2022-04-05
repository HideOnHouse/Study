#include "stdio.h"
#include "limits.h"
#include "stdlib.h"

int top_down_rod_cutting(int *price, int length) {
    if (length == 0) {
        return 0;
    } else {
        int ret = INT_MIN;
        int temp;
        for (int i = 1; i <= length; ++i) {
            temp = price[i - 1] + top_down_rod_cutting(price, length - i);
            if (ret < temp) {
                ret = temp;
            }
        }
        return ret;
    }
}

int rod_cutting_aux(const int *price, int length, int *r) {
    int ret;
    if (r[length] >= 0) {
        return r[length];
    }
    if (length == 0) {
        ret = 0;
    } else {
        ret = INT_MIN;
        int temp;
        for (int i = 1; i <= length; ++i) {
            temp = price[i - 1] + rod_cutting_aux(price, length - i, r);
            if (ret < temp) {
                ret = temp;
            }
        }
    }
    r[length] = ret;
    return ret;
}

int memo_rod_cutting(const int *price, int length) {
    int r[length + 1];
    for (int i = 0; i <= length; ++i) {
        r[i] = INT_MIN;
    }
    return rod_cutting_aux(price, length, r);
}

int bottom_up_rod_cutting(const int *price, int length) {
    int r[length + 1];
    int ret;
    int temp;
    r[0] = 0;
    for (int i = 1; i <= length; ++i) {
        ret = INT_MIN;
        for (int j = 1; j <= i; ++j) {
            temp = price[j - 1] + r[i - j];
            if (ret < temp) {
                ret = temp;
            }
        }
        r[i] = ret;
    }
    return r[length];
}

int *extended_bottom_up_cut_rod(const int *price, int length) {
    int r[length + 1];
    int *s = malloc(sizeof(int) * sizeof(length + 1));
    int q;
    int temp;
    r[0] = 0;
    for (int i = 1; i <= length; ++i) {
        q = INT_MIN;
        for (int j = 1; j <= i; ++j) {
            temp = price[j - 1] + r[i - j];
            if (q < temp) {
                q = temp;
                s[i] = j;
            }
        }
        r[i] = q;
    }
    return s;
}

int main() {
    int p[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 26};
    int length = sizeof(p) / sizeof(int);
    int *result = malloc(sizeof(int));
    *result = top_down_rod_cutting(p, length);
    printf("top down: %d\n", *result);
    *result = memo_rod_cutting(p, length);
    printf("memo top down: %d\n", *result);
    *result = bottom_up_rod_cutting(p, length);
    printf("bottom up: %d\n", *result);
    free(result);
    result = extended_bottom_up_cut_rod(p, length);
    while (length > 0) {
        printf("%d,", result[length]);
        length -= result[length];
    }
    printf("\n");
    return 0;
}
