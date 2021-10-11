#include "stdio.h"

void hanoi_tower(int num_disk, unsigned long long int m) {
    unsigned long long int src;
    unsigned long long int dst;
    if (num_disk % 2 == 0) {
        src = (m & m - 1) % 3;
        dst = ((m | m - 1) + 1) % 3;
    } else {
        src = (m & m - 1) % 3;
        dst = ((m | m - 1) + 1) % 3;
    }
    printf("%llu ", src + 1);
    printf("%llu\n", dst + 1);
}

int main() {
    int num_case;
    scanf("%d", &num_case);
    for (int i = 0; i < num_case; ++i) {
        int num_disk;
        unsigned long long int k;
        scanf("%d %llu", &num_disk, &k);
        hanoi_tower(num_disk, k);
    }
    return 0;
}
