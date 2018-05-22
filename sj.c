#include <stdio.h>
#include <stdlib.h> 

struct stack{
	char statement[80];
	char stack[80];
	char prior[80];
	char postfix[80];
};
typedef struct stack Stack;
Stack* s1=(Stack*)malloc(sizeof(Stack)*80);
int top=0, fixnum=0, final=0;

int push(char x);
int main()
{
	int i;
	gets((*s1).statement);
	for(i=0; (*s1).statement[i]!=0; i++){
		if((*s1).statement[i]=='\r') break;
		if((*s1).statement[i]>='0'&&(*s1).statement[i]<='9'){
			(*s1).postfix[fixnum]=(*s1).statement[i];
			fixnum++;
		}		
		if((*s1).statement[i]=='+'||(*s1).statement[i]=='-'
		||(*s1).statement[i]=='*'||(*s1).statement[i]=='/') push((*s1).statement[i]);
	}	
	final=1;
	push(1);	
	for(i=0; i<80; i++){
		printf("%c", (*s1).postfix[i]);
	}
}

push(char x)
{
	int i;
	char pri;
	
	if(final==0)
	{
	if(x=='*'||x=='/') pri='1';
	else pri='2';
	(*s1).prior[top]=pri;
	if(top>0){
		if((*s1).prior[top-1]<(*s1).prior[top]){
			for(i=top-1; i>=0; i--){
				(*s1).postfix[fixnum]=(*s1).stack[i];
				fixnum++;
				(*s1).stack[i]='\0';
			}
			(*s1).prior[0]=(*s1).prior[top];
			top=0;
		}
		if((*s1).prior[top-1]==(*s1).prior[top]){
			(*s1).postfix[fixnum]=(*s1).stack[top-1];
			fixnum++;
			top--;
		}
	}
	(*s1).stack[top]=x;
	top++;
	}
	
	if(final==1){
		for(i=top-1; i>=0; i--){
			(*s1).postfix[fixnum]=(*s1).stack[i];
			fixnum++;
			(*s1).stack[i]='\0';
		}
	}
}
