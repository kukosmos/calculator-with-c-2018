#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0
#define MAX_BUF 80

#define OP_NODE 0
#define NU_NODE 1

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

// char stack
struct __char_node {
    char element;
    struct __char_node * next;
};
typedef struct __char_node char_node_t;

struct __char_stack {
    char_node_t * top;
};
typedef struct __char_stack char_stack_t;

char_stack_t * create_char_stack () {
    char_stack_t * this = (char_stack_t *) malloc (sizeof (char_stack_t));
    this->top = NULL;
    return this;
}

void char_push (char_stack_t * this, char c) {
    char_node_t * node = (char_node_t *) malloc (sizeof (char_node_t));
    node->element = c;
    node->next = this->top;
    this->top = node;
}

int is_char_empty (char_stack_t * this) {
    return this->top == NULL;
}

char char_pop (char_stack_t * this) {
    char_node_t * del = this->top;
    char c = del->element;
    this->top = del->next;
    free (del);
    return c;
}

void delete_char_stack (char_stack_t * this) {
    char_node_t * node = this->top;
    while (node != NULL) {
        char_node_t * del = node;
        node = node->next;
        free (del);
    }
    free (this);
}

// int stack
struct __int_node {
    int element;
    struct __int_node * next;
};
typedef struct __int_node int_node_t;

struct __int_stack {
    int_node_t * top;
};
typedef struct __int_stack int_stack_t;

int_stack_t * create_int_stack () {
    int_stack_t * this = (int_stack_t *) malloc (sizeof (int_stack_t));
    this->top = NULL;
    return this;
}

void int_push (int_stack_t * this, int n) {
    int_node_t * node = (int_node_t *) malloc (sizeof (int_node_t));
    node->element = n;
    node->next = this->top;
    this->top = node;
}

int is_int_empty (int_stack_t * this) {
    return this->top == NULL;
}

int int_pop (int_stack_t * this) {
    int_node_t * del = this->top;
    int n = del->element;
    this->top = del->next;
    free (del);
    return n;
}

void delete_int_stack (int_stack_t * this) {
    int_node_t * node = this->top;
    while (node != NULL) {
        int_node_t * del = node;
        node = node->next;
        free (del);
    }
    free (this);
}

// util
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

// main
int main (int argc, char** argv) {
    option_t opt;
    parse_option (&opt, argc, argv);

    FILE * f = fopen (opt.file, "r");
    char buf[MAX_BUF];
    char back_marking[MAX_BUF] = { 0, };

    // back marking expression creation part
    char_stack_t * op_stack = create_char_stack ();
    while (fgets (buf, MAX_BUF, f) != NULL) {
        int i = 0;
        int num;
        char op;
        int end_of_line = FALSE;
        while (!end_of_line) {
            switch (buf[i]) {
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
                back_marking[0] == 0
                    ? sprintf(back_marking, "%d", num)
                    : sprintf (back_marking, "%s %d", back_marking, num);
                break;
            case '+':
            case '-':
                while (!is_char_empty (op_stack)) {
                    op = char_pop (op_stack);
                    if (op == '(') {
                        char_push (op_stack, op);
                        break;
                    }
                    sprintf (back_marking, "%s %c", back_marking, op);
                }
                char_push (op_stack, buf[i]);
                break;
            case '*':
            case '/':
                while (!is_char_empty (op_stack)) {
                    op = char_pop (op_stack);
                    if (op == '(' || op == '+' || op == '-') {
                        char_push (op_stack, op);
                        break;
                    }
                    sprintf (back_marking, "%s %c", back_marking, op);
                }
                char_push (op_stack, buf[i]);
                break;
            case '(':
                char_push (op_stack, buf[i]);
                break;
            case ')':
                while (TRUE) {
                    op = char_pop (op_stack);
                    if (op == '(') {
                        break;
                    }
                    sprintf(back_marking, "%s %c", back_marking, op);
                }
                break;
            case ' ':
            case '\n':
            case '\t':
                break;
            default:
                end_of_line = TRUE;
            }
            i++;
        }
    }
    while (!is_char_empty (op_stack)) {
        sprintf (back_marking, "%s %c", back_marking, char_pop (op_stack));
    }
    delete_char_stack (op_stack);
    fclose (f);

    // calculate back marking expression
    int_stack_t * num_stack = create_int_stack ();
    int end_of_expression = FALSE;
    int i = 0;
    int num;
    int n1;
    int n2;
    while (!end_of_expression) {
        switch (back_marking[i]) {
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
            num = find_number (back_marking, &i, MAX_BUF);
            // push number into stack
            int_push (num_stack, num);
            break;
        
        // operators
        case '+':
            // pop two numbers from stack;
            // notice that popped numbers are in REVERSE order
            n2 = int_pop (num_stack);
            n1 = int_pop (num_stack);
            // push calculated number into stack
            int_push (num_stack, n1 + n2);
            break;
        case '-':
            // do as same as +
            n2 = int_pop (num_stack);
            n1 = int_pop (num_stack);
            int_push (num_stack, n1 - n2);
            break;
        case '*':
            n2 = int_pop (num_stack);
            n1 = int_pop (num_stack);
            int_push (num_stack, n1 * n2);
            break;
        case '/':
            n2 = int_pop (num_stack);
            n1 = int_pop (num_stack);
            int_push (num_stack, n1 / n2);
            break;

        // whitespaces
        case ' ':
        case '\n':
        case '\t':
            // discard whitespaces
            break;

        default:
            end_of_expression = TRUE;
        }
        i++;
    }

    // pop last number from stack
    printf ("%d\n", int_pop (num_stack));

    delete_int_stack (num_stack);

    return 0;
}