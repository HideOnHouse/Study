// 유니코드 자음, 모음, 초/중/종성 코드 -- UTF-8 출력
//	C> a.exe > output.txt
//		--> output.txt를 메모장에서 확인
// 국민대학교 소프트웨어학부 강승식
#include <stdio.h>

int main() {
    printf("%c%c%c", 0xEF, 0xBB, 0xBF);    // UTF-8 BOM code
    printf("A. %c%c%c\n", 0xEA, 0xB0, 0x80);    // '가'
    printf("B. %c%c%c\n", 0xED, 0x9E, 0xA3);    // '힣'

    return 0;
}
