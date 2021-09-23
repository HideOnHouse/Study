/*
	�����ڵ� 11,172�ڸ� ����ϴ� ���α׷� -- UTF-16 BE ���
		C> a.exe -- output.txt�� �޸��忡�� Ȯ��
	���δ��б� ����Ʈ�����к� ���½�
*/
#include <stdio.h>

int main() {
    int i, j;
    FILE *fp;

    fp = fopen("output.txt", "wb");

    fprintf(fp, "%c%c", 0xFE, 0xFF);    // BOM �ڵ� -- Big Endian
    for (i = 0xAC00, j = 0; j < 11172; i++, j++) {
//        printf("%c%c: 0x%x\n", (i >> 8) & 0xFF, i & 0xFF, i);
        fprintf(fp, "%c%c", (i >> 8) & 0xFF, i & 0xFF);    // �ѱ� ���� -- ��) '��'
        fprintf(fp, "%c%c", 0x00, ':');
        fprintf(fp, "%c%c", 0x00, ' ');
        fprintf(fp, "%c%c", 0x00, '0');
        fprintf(fp, "%c%c", 0x00, 'x');
        // ���⿡ �ѱ������� '�����ڵ� 16���� �ڵ�'�� ����Ϸ��� ��� �ؾ� �ұ��?
        char buffer[5];
        sprintf(buffer, "%x", i);
        for (int k = 0; k < 4; ++k) {
            fprintf(fp, "%c%c", 0x00, buffer[k]);
        }
        fprintf(fp, "%c%c", 0x00, 0x0D);    // CR ����
        fprintf(fp, "%c%c", 0x00, 0x0A);    // LF ����
    }
    fclose(fp);
    puts("File <output.txt> has been created!");

    return 0;
}
