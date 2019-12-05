#include <stdio.h>
#include <stdlib.h>
#pragma once
#define false   0
#define true    1
#define bool int

typedef void* Element;

typedef struct {
	Element* data;
	int count;
	int size;
}List;

bool isEmptyList(List* pList) {
	if (pList->count == 0) {
		return true;
	}
	return false;
}

bool isFullList(List* pList) {
	if (pList->count == pList->size) {
		return true;
	}
	return false;
}

List* createList(int size) {
	List* pList = (List*)malloc(sizeof(List));
	if (pList == NULL) {
		printf("[Warning]Not enough memory.\n");
		return NULL;
	}

	pList->data = (Element*)malloc(sizeof(Element) * size);
	if (pList->data == NULL) {
		printf("[Warning]Not enough memory.\n");
		free(pList);
		return NULL;
	}

	pList->count = 0;
	pList->size = size;
	printf("[Massage]Made new list successfully.\n");

	return pList;
}

void addNodeList(List* pList, Element data) {
	int i = -1;

	if (isFullList(pList)) {
		printf("[Warning] List is now full.");
		return;
	}
	if (pList->count == 0) {
		pList->data[0] = data;
	}
	else {
		for (i = pList->count; i > 0; i--) {
			if (*(int*)pList->data[i - 1] < * (int*)data) {
				pList->data[i] = data;
				break;
			}
			pList->data[i] = pList->data[i - 1];
		}
	}
	if (i == 0) {
		pList->data[0] = data;
	}
	pList->count++;
}

void removeList(List* pList, Element data) {
	int i;
	void* remove;

	if (isEmptyList(pList)) {
		printf("[Warning] List is now empty.\n");
		return;
	}
	for (i = pList->count - 1; i >= 0; i--) {
		if (*(int*)pList->data[i] == *(int*)data) {
			break;
		}
		if (*(int*)pList->data[i] < *(int*)data || i == 0) {
			printf("[Warning] No data in here.\n");
			return;
		}
	}
	remove = pList->data[i];
	for (; i != pList->count - 1; i++) {
		pList->data[i] = pList->data[i + 1];
	}
	free(remove);
	pList->count--;
}

void searchList(List* pList, Element value) {
	int i;
	for (i = 0; i < pList->count; i++) {
		if (*(int*)pList->data[i] == *(int*)value) {
			printf("My List has %d\n", *(int*)value);
			return;
		}
	}
	printf("My List does not have %d\n", *(int*)value);
}

void destroyList(List* pList) {
	int i;
	for (i = 0; i < pList->count; i++) {
		free(pList->data[i]);
	}
	free(pList);
	printf("Successfully destroyed list.\n");
}


int listCount(List* pList) {
	return pList->count;
}
