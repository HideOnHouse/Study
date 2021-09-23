// À¯´ÏÄÚµå ÀÚÀ½, ¸ğÀ½, ÃÊ/Áß/Á¾¼º ÄÚµå -- UTF-16 BE Ãâ·Â
//	C> a.exe > output.txt
//		--> output.txt¸¦ ¸Ş¸ğÀå¿¡¼­ È®ÀÎ
// ±¹¹Î´ëÇĞ±³ ¼ÒÇÁÆ®¿ş¾îÇĞºÎ °­½Â½Ä
#include <stdio.h>

int main() {
	int i; int ch;

	putchar(0xFE); putchar(0xFF);	// BOM code: UTF-16 BE 
	putchar(0xAC); putchar(0x00);	// '°¡'
	putchar(0xD7); putchar(0xA3);	// 'ÆR'
//	putchar(0x00); putchar('\n');	// LF(ÁÙ¹Ù²Ş ¹®ÀÚ)

	ch = 0x3131;	// ÀÚÀ½: 0x3131
	for (i=0; i < 30; i++) {	// ÃÊ¼º Ãâ·Â
		putchar((ch >> 8) & 0x00FF); putchar(ch & 0x00FF);
		ch ++;
	}

	ch = 0x314F;	// ¸ğÀ½: 0x314F
	for (i=0; i < 21; i++) {	// ÃÊ¼º Ãâ·Â
		putchar((ch >> 8) & 0xFF); putchar(ch & 0xFF);
		ch ++;
	}

	ch = 0x11A8;	// ÃÊ¼º: 0x1100, Áß¼º: 0x1161, Á¾¼º: 0x11A8
	for (i=0; i < 27; i++) {	// ÃÊ¼º Ãâ·Â
		putchar((ch >> 8) & 0xFF); putchar(ch & 0xFF);
		ch ++;
	}

	// <Âü°í> ÃÊ¼º Ãâ·ÂÀÌ ¾ÈµÇ´Â °ÍµéÀÌ ÀÖÀ½
	ch = 0x1100;	// ÃÊ¼º: 0x1100, Áß¼º: 0x1161, Á¾¼º: 0x11A8
	for (i=0; i < 19; i++) {	// ÃÊ¼º Ãâ·Â
		putchar((ch >> 8) & 0xFF); putchar(ch & 0xFF);
		//putchar(0x00); putchar(0x0a);	// LF(ÁÙ¹Ù²Ş ¹®ÀÚ)
		ch ++;
	}

	return 0;
}
