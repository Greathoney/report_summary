#define _CRT_SECURE_NO_WARNINGS
#include "linear_linked_list.h"

void printList(List* pList) {
	ListNode* pLoc;
	printf("The current status of List: ");
	if (listCount(pList) != 0) {
		pLoc = pList->head;
		while (pLoc) {
			printf("%d, ", *(int*)pLoc->data);
			pLoc = pLoc->next;
		}
		printf("\b\b ");
	}
	printf("\n");
}

int main(void) {
	int menu, value;
	int* pNum;

	List* l1 = createList();

	while (true) {
		printf("In (0), Search (1), Out (2), Exit (3): ");
		scanf("%d", &menu);

		switch (menu) {
		case 0:
			pNum = (int*)malloc(sizeof(int));

			printf("Input: ");
			scanf("%d", pNum);
			addNodeList(l1, pNum);
			printList(l1);
			break;

		case 1:
			printf("Search: ");
			scanf("%d", &value);
			searchList(l1, &value);
			printList(l1);
			break;

		case 2:
			printf("Out: ");
			scanf("%d", &value);
			removeList(l1, &value);
			printList(l1);
			break;

		case 3:
			printf("Successfully program exited.\n");
			return 0;
		}
		printf("\n");
	}

	return -1;
}
