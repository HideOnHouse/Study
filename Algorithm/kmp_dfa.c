#include "stdio.h"
#include "string.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define UNIQUE 3

int is_suffix(const char *p, int k, int q, char a) {
    if (p[k - 1] != a) {
        return 0;
    }
    for (int i = 0; i < k - 1; ++i) {
        if (p[i] != p[q - k + i + 1]) {
            return 0;
        }
    }
    return 1;
}

void constructDFA(const char *pattern, int pattern_len, int *output) {
    for (int q = 0; q <= pattern_len; ++q) {
        for (int i = 0; i < UNIQUE; ++i) {
            int k = MIN(pattern_len, q + 1);
            while (k) {
                if (is_suffix(pattern, k, q, (char) (65 + i))) {
                    break;
                }
                --k;
            }
            output[q * UNIQUE + i] = k;
        }
    }
}

int DFAmatching(const char *text, int text_len, int pattern_len, const int *DFA) {
    int count = 0;
    int head = 0;
    int idx;
    for (int i = 0; i < text_len && head < text_len; ++i) {
        idx = UNIQUE * head + text[i] - 65; // 'A' == 65
        head = DFA[idx];
        if (head == pattern_len) {
            ++count;
        }
    }
    return count;
}

int main() {
    int num_case, pattern_len, text_len, count;
    scanf("%d", &num_case);
    char pattern[1001];
    char text[1001];
    for (int _ = 0; _ < num_case; ++_) {
        scanf("%s", pattern);
        scanf("%s", text);

        count = 0;
        pattern_len = (int) strlen(pattern);
        text_len = (int) strlen(text);

        int DFA[UNIQUE * (pattern_len + 1)];
        DFA[0] = 1;
        constructDFA(pattern, pattern_len, DFA);
        for (int *i = DFA; i < DFA + sizeof(DFA) / sizeof(int); ++i) {
            if (*i) {
                ++count;
            }
        }
        printf("%d %d\n", count, DFAmatching(text, text_len, pattern_len, DFA));
    }
    return 0;
}
