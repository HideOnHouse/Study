#include "stdio.h"
#include "stdlib.h"

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
    while (arr[4] != -1) {
        char buffer[1024];
        printf("Please input index and value (12 1)\n>>>");
        scanf("%[^\n]s", buffer);
        char *end;
        int idx = strtol(buffer, &end, 10);
        int value = strtol(end, NULL, 10);
        arr[idx] = value;
        for (int i = 0; i < 4; ++i) {
            printf("%d ", *(arr + i));
        }
        printf("\n");
        fflush(stdin);
    }
    return 0;
}