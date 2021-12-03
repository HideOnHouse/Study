#include "stdio.h"
#include "string.h"

void constructDFA(const char *pattern, int n, int *fail) {
    for (int i = 1, j = 0; i < pattern_len; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = output[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            output[i] = ++j;
        } else {
            output[i] = 0;
        }
    }
}

int get_match_count(const char *text, int text_len, const char *pattern, int pattern_len, int *fail) {
    int count = 0;
    int head = 0;
    for (int i = 0; i < text_len; ++i) {
        while (head > 0 && pattern[head] != text[i]) {
            head = fail[head - 1];
        }
        if (pattern[head] == text[i]) {
            ++head;
        }
        if (head == pattern_len) {
            ++count;
            head = fail[head - 1];
        }
    }
    return count;
}

int main() {
    int num_case, pattern_len, text_len;
    scanf("%d", &num_case);
    char pattern[1001];
    char text[1001];
    for (int _ = 0; _ < num_case; ++_) {
        scanf("%s", pattern);
        scanf("%s", text);

        pattern_len = (int) strlen(pattern);
        text_len = (int) strlen(text);

        int fail[pattern_len];
        fail[0] = 0;
        constructDFA(pattern, pattern_len, fail);
        for (int i = 0; i < pattern_len; ++i) {
            printf("%d ", fail[i]);
        }
        printf("\n");

        printf("%d\n", get_match_count(text, text_len, pattern, pattern_len, fail));
    }
    return 0;
}
