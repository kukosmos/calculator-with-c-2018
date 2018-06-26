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
	//	<파일을 직접 입력받을 경우> 
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
    // 입력 파일의 이름은 opt.file에 저장되어 있다고 생각하면 됩니다.
    // scanf 등을 이용하여 코딩해서 확인하고, 제출 할 때는 이 템플릿을 적용하여 제출 하면 됩니다.
    
    // 윈도우에서만 쓸 수 있는 _s 함수를 사용하지 않습니다.
    // 맨 윗줄에 아래의 선언을 추가하면 됩니다.
    // #define _CRT_SECCURE_NO_WARNINGS

    return 0;
}

