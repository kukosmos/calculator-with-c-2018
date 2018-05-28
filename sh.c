/**********************************
* 링크드 리스트를 이용한 스택의 구현 *
* 스택 : 나중에 들어간 값이         *
*        처음나오는 자료구조        *
***********************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 100 // 최대 입력 문자열 길이 ('\0' 포함)

// 스택안에 정보를 저장하는 노드
struct __node {
    char c; // 노드에 저장되는 값
    struct __node * next;   // 다음 노드를 가리키는 포인터
};
typedef struct __node node_t;

// 스택
struct __stack {
    node_t * top;   // 탑
};
typedef struct __stack stack_t;

// 스택 생성
stack_t * create_stack ();
// 스택 삭제
void delete_stack (stack_t * stack);
// 스택에 값 삽입
void push (stack_t * stack, char c);
// 스택에서 갑 삭제
char pop (stack_t * stack);
// 스택이 비어있는지 검사
int is_empty (stack_t * stack);

int main (void) {
    char buf[MAX_BUF];
    stack_t * stack = create_stack ();  // 스택 생성
    fgets (buf, MAX_BUF, stdin);    // 입력
    int i = 0;
    // 입력 받은 문자열의 모든 값을 스택에 삽입
    while (buf[i] != 0 && buf[i] != '\n' && i < MAX_BUF) {
        push (stack, buf[i]);
        i++;
    }
    
    // 스텍에서 모든 값을 꺼내 출력
    while (!is_empty (stack)) {
        printf ("%c", pop (stack));
    }
    printf("\n");

    // 스택 삭제
    delete_stack (stack);
    
    return 0;
}

// 스택 생성
stack_t * create_stack () {
    stack_t * stack = (stack_t *) malloc (sizeof (stack));  // 스택을 위한 새로운 메모리를 할당
    stack->top = NULL;
    return stack;
}

// 스텍 삭제
void delete_stack (stack_t * this) {
    node_t * node = this->top;
    node_t * del;
    while (node != NULL) {  // 만약에 스택에 삭제 안된 노드가 존재 한다면 모든 노드 삭제
        del = node;
        node = node->next;
        free (del); // 노드 삭제
    }
    free (this);    // 스택 삭제
}

// 스택에 값 삽입
void push (stack_t * this, char c) {
    node_t * node = (node_t *) malloc (sizeof (node_t));    // 노드를 위한 새로운 메모리를 할당

    // 새로운 노드의 값 설정
    node->c = c;

    // 스택안의 링크드 리스트의 구조 변경
    node->next = this->top;
    this->top = node;
}

// 스택에 값 삭제
char pop (stack_t * this) {
    // 반환할 값 설정
    node_t * del = this->top;
    char c = del->c;

    // 스택안의 링크드 리스트의 구조 변경
    this->top = del->next;
    
    free (del); // 값을 반환하고 필요없는 할당된 메모리를 삭제
    return c;
}

// 스택이 비어있는지 검사
int is_empty (stack_t * this) {
    return this->top == NULL;   // 만약 탑에 값이 없다면 스택은 비어있음
}