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
		
	argv[1]="sj.txt";
	option_t opt;
    parse_option (&opt, argc, argv);
    
    FILE *fp = fopen(opt.file, "r"); 
    
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
    
    // TODO
    // �Է� ������ �̸��� opt.file�� ����Ǿ� �ִٰ� �����ϸ� �˴ϴ�.
    // scanf ���� �̿��Ͽ� �ڵ��ؼ� Ȯ���ϰ�, ���� �� ���� �� ���ø��� �����Ͽ� ���� �ϸ� �˴ϴ�.
    
    // �����쿡���� �� �� �ִ� _s �Լ��� ������� �ʽ��ϴ�.
    // �� ���ٿ� �Ʒ��� ������ �߰��ϸ� �˴ϴ�.
    // #define _CRT_SECCURE_NO_WARNINGS

    return 0;
}

