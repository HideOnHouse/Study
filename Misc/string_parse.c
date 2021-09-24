#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main() {
    char buffer[BUFSIZ];
    char *tok;
    int a, b, difference;
    int sum = 0;
    while (fgets(buffer, BUFSIZ, stdin)) {
        tok = strtok(buffer, " ");
        a = strtol(tok, NULL, 10);
        tok = strtok(NULL, " ");
        b = strtol(tok, NULL, 10);
        difference = a - b;
        sum += difference;
//        printf("target level: %03d, current level: %03d, difference: %03d\n", values[0], values[1], difference);
    }
//    printf("# expected union increase value: %d\n", sum);
    return 0;
}