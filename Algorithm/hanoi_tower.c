#include "stdio.h"

void hanoi_tower(int num_disk, int a, int b, int c, unsigned long long *k) {
    unsigned long long m = (unsigned long long) 1 << (num_disk - 1);
    if (num_disk == 1 || *k == m) {
        printf("%d %d\n", a, c);
        return;
    }
    if (*k < m) {
        hanoi_tower(num_disk - 1, a, c, b, k);
    } else {
        *k = *k - m;
        hanoi_tower(num_disk - 1, b, a, c, k);
    }
}

int main() {
    int num_case;
    int num_disk;
    unsigned long long int k;
    scanf("%d", &num_case);
    for (int i = 0; i < num_case; ++i) {
        scanf("%d %llu", &num_disk, &k);
        hanoi_tower(num_disk, 1, 2, 3, &k);
    }
    return 0;
}
