#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 100

struct __node {
    char val;
    struct __node * next;
};
typedef struct __node Node;

struct __stack {
    struct __node * top;
};
typedef struct __stack Stack;

Stack * create_stack () {
    Stack * this = (Stack *) malloc (sizeof (Stack));
    this->top = NULL;
    return this;
}

void push (Stack * this, char c) {
    Node * node = (Node *) malloc (sizeof (char));
    node->val = c;
    node->next = this->top;
    this->top = node;
}

char pop (Stack * this) {
    Node * del = this->top;
    char c = del->val;
    this->top = del->next;
    free (del);
    return c;
}

int is_empty (Stack * this) {
    return this->top == NULL;
}

int main (int argc, char ** argv) {
    char buf [MAX_BUF];
    Stack * stack = create_stack ();
    printf ("input: ");
    fgets (buf, MAX_BUF, stdin);

    int i = 0;
    while (buf [i] != 0) {
        push (stack, buf [i]);
        i++;
    }

    printf ("inverse: ");
    while (!is_empty (stack)) {
        printf ("%c", pop (stack));
    }
    printf ("\n");

    return 0;
}