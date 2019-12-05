#include <stdio.h>
#include <malloc.h>
#pragma once
#define false   0
#define true    1
#define bool int


typedef void* Element;

typedef struct tListNode {
	Element data;
	struct tListNode* next;
} ListNode;

typedef struct {
	int count;
	ListNode* pos;
	ListNode* head;
} List;

void _insertList(List* pList, ListNode* pPre, Element data) {
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));
	if (!pNewNode) {
		printf("[Warning] Not enough memory.\n");
		return;
	}

	if (pPre == NULL) { // pList has 0 count.
		pNewNode->next = pList->head;
		pList->head = pNewNode; // directs each other.
	}
	else {
		pNewNode->next = pPre->next;
		pPre->next = pNewNode;
	}
	pNewNode->data = data;

	pList->pos = NULL;
	pList->count++;
}

bool _searchList(List* pList, ListNode** ppPre, ListNode** ppLoc, Element data) {
	for (*ppPre = NULL, *ppLoc = pList->head; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->next) {
		if (*(int*)(*ppLoc)->data == *(int*)data) { // int only code
			return true;
		}
		else if (*(int*)(*ppLoc)->data > * (int*)data) { //int only code
			break;
		}
	}
	return false;
}

void _deleteList(List* pList, ListNode* pPre, ListNode* pLoc) {
	if (pPre == NULL) {
		pList->head = pLoc->next;
	}
	else {
		pPre->next = pLoc->next;
	}

	free(pLoc);
	pList->count--;
}

List* createList() {
	List* pNewList = (List*)malloc(sizeof(List));
	if (!pNewList) {
		printf("[Warning] Not enough memory.\n");
		return NULL;
	}

	pNewList->count = 0;
	pNewList->head = NULL;

	printf("Successfully created list.\n");
	return pNewList;
}

void addNodeList(List* pList, Element data) {
	ListNode* pPre = NULL, * pLoc = NULL;

	if (!_searchList(pList, &pPre, &pLoc, data)) {
		_insertList(pList, pPre, data);
	}
	else {
		printf("[Warning] List has same value.\n");
	}
}

void removeList(List* pList, Element data) {
	ListNode* pPre = NULL, * pLoc = NULL;
	if (_searchList(pList, &pPre, &pLoc, data)) {
		_deleteList(pList, pPre, pLoc);
	}
	else {
		printf("[Warning] There's no data to remove.\n");
	}
}

Element keyList(List* pList, int key) {
	int i;
	ListNode* pLoc = NULL;

	if (pList->count <= key) {
		printf("[Warning] Key must be smaller than length of list.\n");
		return NULL;
	}

	if (key >= 0) {
		pLoc = pList->head;
		for (i = 0; i != key; i++) {
			pLoc = pLoc->next;
		}
		return pLoc->data;
	}
	else {
		printf("[Warning] Key must be 0 or postive integer.\n");
		return NULL;
	}
}

void searchList(List* pList, Element value) {
	ListNode* pPre = NULL, * pLoc = NULL;
	if (_searchList(pList, &pPre, &pLoc, value)) {
		printf("My List has %d.\n", *(int*)value); // int only code
	}
	else {
		printf("My List doesn't have %d.\n", *(int*)value); // int only code
	}
}

void destroyList(List* pList) {
	ListNode* pDel = NULL, * pNext = NULL;

	for (pDel = pList->head; pDel != NULL; pDel = pNext) {
		pNext = pDel->next;
		free(pDel);
	}

	free(pList);
	printf("Successfully destroyed list.\n");
}

bool traverseList(List* pList, int fromWhere, Element* pDataOut) {
	if (fromWhere == 0 || pList->pos == NULL) {
		pList->pos = pList->head;
	}
	else {
		pList->pos = pList->pos->next;
	}

	if (pList->pos != NULL) {
		*pDataOut = pList->pos->data;
		return true;
	}
	else {
		*pDataOut = 0;
		return false;
	}
}

int listCount(List* pList) {
	return pList->count;
}

bool isEmptyList(List* pList) {
	if (pList->count == 0) {
		return true;
	}
	return false;
}
