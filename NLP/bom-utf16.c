// �����ڵ� ����, ����, ��/��/���� �ڵ� -- UTF-16 BE ���
//	C> a.exe > output.txt
//		--> output.txt�� �޸��忡�� Ȯ��
// ���δ��б� ����Ʈ�����к� ���½�
#include <stdio.h>

int main() {
	int i; int ch;

	putchar(0xFE); putchar(0xFF);	// BOM code: UTF-16 BE 
	putchar(0xAC); putchar(0x00);	// '��'
	putchar(0xD7); putchar(0xA3);	// '�R'
//	putchar(0x00); putchar('\n');	// LF(�ٹٲ� ����)

	ch = 0x3131;	// ����: 0x3131
	for (i=0; i < 30; i++) {	// �ʼ� ���
		putchar((ch >> 8) & 0x00FF); putchar(ch & 0x00FF);
		ch ++;
	}

	ch = 0x314F;	// ����: 0x314F
	for (i=0; i < 21; i++) {	// �ʼ� ���
		putchar((ch >> 8) & 0xFF); putchar(ch & 0xFF);
		ch ++;
	}

	ch = 0x11A8;	// �ʼ�: 0x1100, �߼�: 0x1161, ����: 0x11A8
	for (i=0; i < 27; i++) {	// �ʼ� ���
		putchar((ch >> 8) & 0xFF); putchar(ch & 0xFF);
		ch ++;
	}

	// <����> �ʼ� ����� �ȵǴ� �͵��� ����
	ch = 0x1100;	// �ʼ�: 0x1100, �߼�: 0x1161, ����: 0x11A8
	for (i=0; i < 19; i++) {	// �ʼ� ���
		putchar((ch >> 8) & 0xFF); putchar(ch & 0xFF);
		//putchar(0x00); putchar(0x0a);	// LF(�ٹٲ� ����)
		ch ++;
	}

	return 0;
}
