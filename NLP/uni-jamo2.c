/*
	유니코드 한 글자에 대한 초성/중성/종성을 출력하는 프로그램
		C> a.exe i	// i값: 1~11172
	국민대학교 소프트웨어학부 강승식
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int ch=0xAC00+12;	// 유니코드 한글 -- 초/중/종 분해 대상, 0xAC00~0xD7A3

	int i, cho, jung, jong;
	int cho_base=0x1100;	// 유니코드 초성 'ㄱ'
	int jung_base=0x1161;	// 유니코드 중성 'ㅏ'
	int jong_base=0x11A8;	// 유니코드 종성 'ㄱ'
	FILE *fp;

	if (argc == 2)
		ch = 0xAC00 + atoi(argv[1]) - 1;	// i번째 한글 음절

	i = ch - 0xAC00;
	cho = i / (21*28);
	jung = (i / 28) % 21;
	jong = i % 28;
	printf("유니코드 -- U+%x\n", ch);
	printf("\t초성:중성:종성(offset 값)\t--> %d : %d : %d\n", cho, jung, jong);

	cho += cho_base;
	jung+= jung_base;
	jong+= jong_base-1;
	printf("\t초성:중성:종성(유니코드 값)\t--> U+%x : U+%x : U+%x\n", cho, jung, jong);

	fp = fopen("output.txt", "wb");	// 출력할 파일
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
