/*
	�����ڵ� 11,172�ڸ� ����ϴ� ���α׷� -- UTF-8 ���
		C> a.exe -- output.txt�� �޸��忡�� Ȯ��
	���δ��б� ����Ʈ�����к� ���½�
*/
#include <stdio.h>

int main() {
	int i, j;
	FILE *fp;
	char utf8[4]={0};

	fp = fopen("output.txt", "w");

	//fprintf(fp, "%c%c%c", 0xEF, 0xBB, 0xBF);	// BOM �ڵ�
	for (i=0xAC00, j=0; j < 11172; i++, j++) {
		utf8[0] = 0xE0;
        utf8[0] |= ((i >> 12) & 0x000F);
		utf8[1] = 0x80;
        utf8[1] |= ((i >> 6) & 0x003F);
		utf8[2] = 0x80;
        utf8[2] |= (i & 0x003F);
		fprintf(fp, "%s", utf8);
		fprintf(fp, ": 0x%x\n", i);
	}
	fclose(fp);
	puts("FIle <output.txt> has been created!");
	
	return 0;
}
