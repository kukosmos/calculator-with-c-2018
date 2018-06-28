#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECCURE_NO_WARNINGS
#define MAX_BUF 80
#define WHITE_SPACE " \t\n"

/* parsing arguments */
/* DO NOT modify */
struct __option {
    char file[80];
};
typedef struct __option option_t;

void parse_option (option_t * opt, int argc, char** argv) {
    if (argc != 2) {
        printf ("Usage: main <testfile>\n");
    }
    strcpy (opt->file, argv[1]);
}
/* DO NOT modify */

int main (int argc, char** argv) {
	//	<������ ���� �Է¹��� ���> 
	/*FILE *fp = fopen("sj.txt", "w");
	{
		char content[80];
		gets(content);
		fprintf(fp, "%s", &content);
	}
	fclose(fp);
	system("cls");
	*/

	// feed back	
	// argv[1]="sj.txt";	// 옵션 파싱하는 부분은 바꾸지 마세요.
	option_t opt;
    parse_option (&opt, argc, argv);
    
    FILE *fp = fopen(opt.file, "r"); 
    
	// feed back
	// 이렇게 쓰면 마지막 줄이 두번 출력되는 현상은 막을 수 있습니다.
	char buf[MAX_BUF];
	while (fgets(buf, MAX_BUF, fp) != NULL) {
		// 그래로 출력이기 때문에 화이트 스페이스를 지울 필요가 없습니다.
		printf("%s", buf);
	}
	/*
    while(!feof(fp))
	{
		char buf[MAX_BUF];
		fgets(buf, MAX_BUF, fp);
		char* token= strtok(buf, WHITE_SPACE);
		while(token)
		{
			printf("%s ", token);
			token= strtok(NULL, WHITE_SPACE);
		}
		printf("\n");
	}
	*/
    
    // TODO
    // �Է� ������ �̸��� opt.file�� ����Ǿ� �ִٰ� �����ϸ� �˴ϴ�.
    // scanf ���� �̿��Ͽ� �ڵ��ؼ� Ȯ���ϰ�, ���� �� ���� �� ���ø��� �����Ͽ� ���� �ϸ� �˴ϴ�.
    
    // �����쿡���� �� �� �ִ� _s �Լ��� ������� �ʽ��ϴ�.
    // �� ���ٿ� �Ʒ��� ������ �߰��ϸ� �˴ϴ�.
    // #define _CRT_SECCURE_NO_WARNINGS

    return 0;
}

