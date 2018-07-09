#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0
#define MAX_BUF 80

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

struct __node {
    char element;
    struct __node * next;
};
typedef struct __node node_t;

struct __stack {
    node_t * top;
};
typedef struct __stack stack_t;

stack_t * create_stack () {
    stack_t * this = (stack_t *) malloc (sizeof (stack_t));
    this->top = NULL;
    return this;
}

void push (stack_t * this, char c) {
    node_t * node = (node_t *) malloc (sizeof (node_t));
    node->element = c;
    node->next = this->top;
    this->top = node;
}

int is_empty (stack_t * this) {
    return this->top == NULL;
}

char pop (stack_t * this) {
    node_t * del = this->top;
    char c = del->element;
    this->top = del->next;
    free (del);
    return c;
}

void delete_stack (stack_t * this) {
    node_t * node = this->top;
    while (node != NULL) {
        node_t * del = node;
        node = node->next;
        free (del);
    }
    free (this);
}

int find_number (char * str, int * i, int max) {
    int result = 0;
    int end_of_num = FALSE;
    while (*i < max) {
        switch (str[*i]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            result *= 10;
            result += str[*i] - '0';
            break;
        default:
            end_of_num = TRUE;
        }
        if (end_of_num) {
            (*i)--;
            break;
        }
        (*i)++;
    }
    return result;
}

int main (int argc, char** argv) {
    option_t opt;
    parse_option (&opt, argc, argv);

    FILE * f = fopen (opt.file, "r");
    char buf[MAX_BUF];
    char result[MAX_BUF] = { 0, };

    // back marking expression creation
    // create stack for operators
    stack_t * stack = create_stack ();

    while (fgets (buf, MAX_BUF, f) != NULL) {
        int i = 0;
        int num;
        char op;
        int end_of_line = FALSE;

        while (!end_of_line) {
            switch (buf[i]) {
            // find number
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                num = find_number (buf, &i, MAX_BUF);
                // if number is first number
                result[0] == 0
                    ? sprintf(result, "%d", num)
                    : sprintf (result, "%s %d", result, num);
                break;

            // operator + and -
            case '+':
            case '-':
                // pop all operators except (
                while (!is_empty (stack)) {
                    op = pop (stack);
                    if (op == '(') {
                        push (stack, op);
                        break;
                    }
                    sprintf (result, "%s %c", result, op);
                }
                push (stack, buf[i]);
                break;
            
            // operator * and /
            case '*':
            case '/':
                // pop only * and /
                while (!is_empty (stack)) {
                    op = pop (stack);
                    if (op == '(' || op == '+' || op == '-') {
                        push (stack, op);
                        break;
                    }
                    sprintf (result, "%s %c", result, op);
                }
                push (stack, buf[i]);
                break;

            // parenthisis part
            case '(':
                // just push (
                push (stack, buf[i]);
                break;
            case ')':
                // pop all operators until meat (
                while (TRUE) {
                    op = pop (stack);
                    if (op == '(') {
                        // discard (
                        break;
                    }
                    sprintf(result, "%s %c", result, op);
                }
                break;

            // whitespaces
            case ' ':
            case '\n':
            case '\t':
                // discard whitespaces
                break;

            default:
                end_of_line = TRUE;
            }
            i++;
        }
    }

    // pop all remaining operators in stack
    while (!is_empty (stack)) {
        sprintf (result, "%s %c", result, pop (stack));
    }
    
    printf("%s\n", result);

    delete_stack (stack);
    fclose (f);

    return 0;
}