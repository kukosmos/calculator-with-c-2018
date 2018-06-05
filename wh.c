#include <stdio.h>

typedef struct stackNode {
	char data;
	struct stackNode *nextPtr;
} StackNode;
typedef StackNode* StackNodePtr;

main() {
	char input[1000];
	int i;

	printf("Enter a line of text: ");
	gets_s(input, 1000);
	
	StackNodePtr topPtr = NULL;
	for(i=0; input[i]; i++) {
		StackNodePtr newPtr;
		newPtr = malloc(sizeof(StackNode));

		if (newPtr != NULL) {
			newPtr->data = input[i];
			newPtr->nextPtr = topPtr;
			topPtr = newPtr;
		}
	}

	printf("\nThe reversed line is: ");
	for (int j = i; j > 0; j--) {
		StackNodePtr tempPtr;
		tempPtr = topPtr;
		printf("%c", topPtr->data);
		topPtr = topPtr->nextPtr;
		free(tempPtr);
	}
	printf("\n");

	system("pause");
}