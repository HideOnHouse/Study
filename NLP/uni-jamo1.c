/*
	유니코드 인코딩/디코딩: UTF-16/BE(16비트 정수값) <-> UTF8(24비트 정수값)
	초성/중성/종성 offset 계산 프로그램

	국민대학교 소프트웨어학부 강승식
*/
#include <stdio.h>

// UTF-16/BE(16비트 정수값) -> UTF-8(24비트 정수값)
int uni2utf8(int uni)
{
	int utf;

	utf = 0x00E00000 | (uni << 4) & 0x000F0000;
	utf |= 0x00008000 | (uni << 2) & 0x00003F00;
	utf |= 0x00000080 | uni & 0x0000003F;

	return utf;
}

// UTF-8(24비트 정수값) -> UTF-16(16비트 정수값)
int utf2uni(int utf)
{
	int uni;

	uni = utf & 0x0000003F;	// last 6 bits in 3rd byte
	uni |= ((utf & 0x00003F00) >> 2);	// 6 bits in 2nd byte
	uni |= ((utf & 0x000F0000) >> 4);	// 4 bits in 1st byte

	return uni;
}

// return value: 0~18
int chosung_index(int uni)
{
	return ((uni-0x0000AC00) / (21*28));
}

// return value: 0~20
int jungsung_index(int uni)
{
	return ((uni-0x0000AC00) % (21*28)) / 28;
}

// return value: 0~27
int jongsung_index(int uni)
{
	return ((uni-0x0000AC00) % 28);
}

int main()
{
	int uni=0xD55C;	// '한' -- 유니코드 1개
	int utf8;
	int cho, jung, jong;

	utf8 = uni2utf8(uni);	// unicode -> utf-8 conversion
	printf("utf-8: 0x%x\n", utf8);

	uni = utf2uni(utf8);	// unicode -> utf-8 conversion
	printf("unicode: U+%x\n", uni);

	cho = chosung_index(uni);
	jung= jungsung_index(uni);
	jong= jongsung_index(uni);

	printf("\tcho = %2d\n", cho);
	printf("\tjung= %2d\n", jung);
	printf("\tjong= %2d\n", jong);
	
	return 0;
}