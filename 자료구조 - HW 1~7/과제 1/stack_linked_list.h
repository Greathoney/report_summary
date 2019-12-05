#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef double Element;

typedef struct tStackNode{
	Element data;
	struct tStackNode* next;
}StackNode;

typedef struct {
	int size;
	int count;
	StackNode* top;
}Stack;

Stack* CreateStack(int size) {
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL) {
		printf("[Warning]Not enough memory.\n");
		return NULL;
	}
	pStack->count = 0;
	pStack->size = size;
	pStack->top = NULL;

	printf("Made new stack successfully.\n");
	return pStack;
}

void Push(Stack* pStack, Element item) {
	StackNode* pNewNode = (StackNode*)malloc(sizeof(StackNode));
	if (pNewNode == NULL) {
		printf("[Warning]Not enough memory.\n");
		return;
	}
	if (pStack->count == pStack->size) {
		printf("[Warning]Stack is now full.\n");
		return;
	}
	pNewNode->data = item;
	pNewNode->next = pStack->top;
	pStack->top = pNewNode;
	pStack->count++;
}

Element Pop(Stack* pStack) {
	if (pStack->count == 0) {
		printf("[Warning]Stack is now empty.\n");
		return 0;
	}

	Element data = pStack->top->data;
	StackNode* next = pStack->top->next;
	free(pStack->top);

	pStack->top = next;
	pStack->count--;

	return data;
}

Element Top(Stack* pStack) {
	if (pStack->count == 0) {
		printf("[Warning]Stack is now empty.\n");
		return 0;
	}

	return pStack->top->data;
}

void DestroyStack(Stack* pStack) {
	if (pStack == NULL) {
		printf("[Warning]Stack is now NULL.\n");
		return;
	}
	
	StackNode* next;
	if (pStack->count >= 1) {
		while (pStack->count == 1) {
			next = pStack->top;
			pStack->top = pStack->top->next;
			free(next);
			pStack->count--;
		}
		free(pStack->top);
	}
	free(pStack);
}

bool IsFullStack(Stack* pStack) {
	if (pStack->count == pStack->size) {
		return true;
	}
	else {
		return false;
	}
}

bool IsEmptyStack(Stack* pStack) {
	if (pStack->count == 0) {
		return true;
	}
	else {
		return false;
	}
}

int CountStackItem(Stack* pStack) {
	return pStack->count;
}


void ClearStack(Stack* pStack) {
	if (pStack == NULL) {
		printf("[Warning]Stack is now NULL.\n");
		return;
	}

	while (pStack->count == 0) {
		StackNode* next = pStack->top->next;
		free(pStack->top);
		pStack->top = next;
		pStack->count--;
	}
}
