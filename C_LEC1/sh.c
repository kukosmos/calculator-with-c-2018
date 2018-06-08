#include <stdio.h>
#include <string.h>

/***** 수정하지 마세요 *****/
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
/***** 수정하지 마세요 *****/

int main (int argc, char** argv) {
    option_t opt;
    parse_option (&opt, argc, argv);

    // TODO
    // 입력 파일의 이름은 opt.file에 저장되어 있다고 생각하면 됩니다.

    return 0;
}