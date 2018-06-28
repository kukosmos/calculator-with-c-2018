#include <stdio.h>
#include <string.h>

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

int main (int argc, char** argv) {
    option_t opt;
    parse_option (&opt, argc, argv);

    FILE * f = fopen (opt.file, "r");
    char buf[80];
    while (fgets(buf, 80, f) != NULL) {
        printf("%s", buf);
    }

    return 0;
}