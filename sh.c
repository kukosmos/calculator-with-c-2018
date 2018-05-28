#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 100

struct __node {
    char c;
    struct __node * next;
};
typedef struct __node node_t;

struct __stack {
    node_t * top;
};
typedef struct __stack stack_t;

stack_t * create_stack ();
void delete_stack (stack_t * stack);
void push (stack_t * stack, char c);
char pop (stack_t * stack);
int is_empty (stack_t * stack);

int main (void) {
    char buf[MAX_BUF];
    stack_t * stack = create_stack ();
    fgets (buf, MAX_BUF, stdin);
    int i = 0;
    while (buf[i] != 0 && buf[i] != '\n' && i < MAX_BUF) {
        push (stack, buf[i]);
        i++;
    }
    
    while (!is_empty (stack)) {
        printf ("%c", pop (stack));
    }
    printf("\n");

    delete_stack (stack);
    
    return 0;
}

stack_t * create_stack () {
    stack_t * stack = (stack_t *) malloc (sizeof (stack));
    stack->top = NULL;
    return stack;
}

void delete_stack (stack_t * this) {
    node_t * node = this->top;
    node_t * del;
    while (node != NULL) {
        del = node;
        node = node->next;
        free (del);
    }
    free (this);
}

void push (stack_t * this, char c) {
    node_t * node = (node_t *) malloc (sizeof (node_t));
    node->c = c;
    node->next = this->top;
    this->top = node;
}

char pop (stack_t * this) {
    node_t * del = this->top;
    char c = del->c;
    this->top = del->next;
    free (del);
    return c;
}

int is_empty (stack_t * this) {
    return this->top == NULL;
}