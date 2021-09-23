/*
	유니코드 11,172자를 출력하는 프로그램 -- UTF-16 BE 출력
		C> a.exe -- output.txt를 메모장에서 확인
	국민대학교 소프트웨어학부 강승식
*/
#include <stdio.h>

int main() {
    int i, j;
    FILE *fp;

    fp = fopen("output.txt", "wb");

    fprintf(fp, "%c%c", 0xFE, 0xFF);    // BOM 코드 -- Big Endian
    for (i = 0xAC00, j = 0; j < 11172; i++, j++) {
//        printf("%c%c: 0x%x\n", (i >> 8) & 0xFF, i & 0xFF, i);
        fprintf(fp, "%c%c", (i >> 8) & 0xFF, i & 0xFF);    // 한글 음절 -- 예) '가'
        fprintf(fp, "%c%c", 0x00, ':');
        fprintf(fp, "%c%c", 0x00, ' ');
        fprintf(fp, "%c%c", 0x00, '0');
        fprintf(fp, "%c%c", 0x00, 'x');
        // 여기에 한글음절의 '유니코드 16진수 코드'를 출력하려면 어떻게 해야 할까요?
        char buffer[5];
        sprintf(buffer, "%x", i);
        for (int k = 0; k < 4; ++k) {
            fprintf(fp, "%c%c", 0x00, buffer[k]);
        }
        fprintf(fp, "%c%c", 0x00, 0x0D);    // CR 문자
        fprintf(fp, "%c%c", 0x00, 0x0A);    // LF 문자
    }
    fclose(fp);
    puts("File <output.txt> has been created!");

    return 0;
}
