// À¯´ÏÄÚµå ÀÚÀ½, ¸ðÀ½, ÃÊ/Áß/Á¾¼º ÄÚµå -- UTF-8 Ãâ·Â
//	C> a.exe > output.txt
//		--> output.txt¸¦ ¸Þ¸ðÀå¿¡¼­ È®ÀÎ
// ±¹¹Î´ëÇÐ±³ ¼ÒÇÁÆ®¿þ¾îÇÐºÎ °­½Â½Ä
#include <stdio.h>

int main() {
    printf("%c%c%c", 0xEF, 0xBB, 0xBF);    // UTF-8 BOM code
    printf("A. %c%c%c\n", 0xEA, 0xB0, 0x80);    // '°¡'
    printf("B. %c%c%c\n", 0xED, 0x9E, 0xA3);    // 'ÆR'

    return 0;
}
