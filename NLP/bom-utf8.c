// �����ڵ� ����, ����, ��/��/���� �ڵ� -- UTF-8 ���
//	C> a.exe > output.txt
//		--> output.txt�� �޸��忡�� Ȯ��
// ���δ��б� ����Ʈ�����к� ���½�
#include <stdio.h>

int main() {
    printf("%c%c%c", 0xEF, 0xBB, 0xBF);    // UTF-8 BOM code
    printf("A. %c%c%c\n", 0xEA, 0xB0, 0x80);    // '��'
    printf("B. %c%c%c\n", 0xED, 0x9E, 0xA3);    // '�R'

    return 0;
}
