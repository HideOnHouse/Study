// KS �ϼ��� �ѱ� �ڵ尪 ���
// �Է�: �ѱ� ����
#include <stdio.h>
#include <string.h>

int main() {
    int i;
    unsigned char a[100];

    printf("Input Hangul word = ");
    fgets(a, 512, stdin);
    for (i = 0; i < strlen(a); i++)
        printf("0x%02x\n", a[i]);
    return 0;
}
