/*
	�����ڵ� �� ���ڿ� ���� �ʼ�/�߼�/������ ����ϴ� ���α׷�
		C> a.exe i	// i��: 1~11172
	���δ��б� ����Ʈ�����к� ���½�
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int ch=0xAC00+12;	// �����ڵ� �ѱ� -- ��/��/�� ���� ���, 0xAC00~0xD7A3

	int i, cho, jung, jong;
	int cho_base=0x1100;	// �����ڵ� �ʼ� '��'
	int jung_base=0x1161;	// �����ڵ� �߼� '��'
	int jong_base=0x11A8;	// �����ڵ� ���� '��'
	FILE *fp;

	if (argc == 2)
		ch = 0xAC00 + atoi(argv[1]) - 1;	// i��° �ѱ� ����

	i = ch - 0xAC00;
	cho = i / (21*28);
	jung = (i / 28) % 21;
	jong = i % 28;
	printf("�����ڵ� -- U+%x\n", ch);
	printf("\t�ʼ�:�߼�:����(offset ��)\t--> %d : %d : %d\n", cho, jung, jong);

	cho += cho_base;
	jung+= jung_base;
	jong+= jong_base-1;
	printf("\t�ʼ�:�߼�:����(�����ڵ� ��)\t--> U+%x : U+%x : U+%x\n", cho, jung, jong);

	fp = fopen("output.txt", "wb");	// ����� ����
	putc(0xFE, fp);	putc(0xFF, fp);	// BOM code

	putc((ch >> 8) & 0xff, fp);
	putc(ch & 0xff, fp);

	putc(0x00, fp); putc(' ', fp);
	putc(0x00, fp); putc('-', fp);
	putc(0x00, fp); putc('-', fp);
	putc(0x00, fp); putc(' ', fp);

	putc((cho >> 8) & 0xff, fp);
	putc(cho & 0xff, fp);

	putc((jung >> 8) & 0xff, fp);
	putc(jung & 0xff, fp);

	putc((jong >> 8) & 0xff, fp);
	putc(jong & 0xff, fp);
	putc('\n', fp);
	fclose(fp);

	printf("File <output.txt> has been created!\n");
	return 0;
}
