#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void* Element;

typedef struct {
	Element* stack;
	int size;
	int top;
}Stack;

Stack* CreateStack(int size) {
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL) {
		printf("[Warning]Not enough memory.\n");
		return NULL;
	}

	pStack->stack = (Element*)malloc(sizeof(Element) * size);
	if (pStack->stack == NULL) {
		printf("[Warning]Not enough memory.\n");
		free(pStack);
		return NULL;
	}

	pStack->size = size;
	pStack->top = -1;
	printf("[Massage]Made new stack successfully.\n");

	return pStack;
}

void Push(Stack* pStack, Element item) {
	if (pStack->size - 1 == pStack->top) {
		printf("[Warning]Stack is now full.\n");
		return;
	}
	pStack->stack[pStack->top++] = item;
}

Element Pop(Stack* pStack) {
	if (pStack->top == -1) {
		printf("[Warning]Stack is now empty.\n");
		return NULL;
	}
	return pStack->stack[--pStack->top];
}

Element Top(Stack* pStack) {
	if (pStack->top == -1) {
		printf("[Warning]Stack is now empty.\n");
		return 0;
	}
	return pStack->stack[pStack->top];
}

void DestroyStack(Stack* pStack) {
	if (pStack == NULL) {
		printf("[Warning]Stack is now NULL.\n");
		return;
	}
	free(pStack);
}

bool IsFullStack(Stack* pStack) {
	if (pStack->size - 1 == pStack->top) {
		return true;
	}
	else {
		return false;
	}
}

bool IsEmptyStack(Stack* pStack) {
	if (pStack->top == -1) {
		return true;
	}
	else {
		return false;
	}
}

int CountStackItem(Stack* pStack) {
	return pStack->top + 1;
}

void ClearStack(Stack* pStack) {
	pStack->top = -1;
}
