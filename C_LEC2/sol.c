#include <stdio.h>
#include <stdlib.h>
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

int main (int argc, char** argv) {
    option_t opt;
    parse_option (&opt, argc, argv);

    FILE * f = fopen (opt.file, "r");
    char buf[80];
    stack_t * stack = create_stack ();

    while (fgets (buf, 80, f) != NULL) {
        int i = 0;
        while (buf[i] != '\0') {
            push (stack, buf[i]);
            i++;
        }
    }

    while (!is_empty (stack)) {
        printf ("%c", pop(stack));
    }
    printf ("\n");

    delete_stack (stack);
    fclose (f);

    return 0;
}