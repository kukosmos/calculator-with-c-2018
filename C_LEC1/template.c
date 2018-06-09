#include <stdio.h>
#include <string.h>

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
    option_t opt;
    parse_option (&opt, argc, argv);

    // TODO
    // 입력 파일의 이름은 opt.file에 저장되어 있다고 생각하면 됩니다.
    // scanf 등을 이용하여 코딩해서 확인하고, 제출 할 때는 이 템플릿을 적용하여 제출 하면 됩니다.
    
    // 윈도우에서만 쓸 수 있는 _s 함수를 사용하지 않습니다.
    // 맨 윗줄에 아래의 선언을 추가하면 됩니다.
    // #define _CRT_SECCURE_NO_WARNINGS

    return 0;
}