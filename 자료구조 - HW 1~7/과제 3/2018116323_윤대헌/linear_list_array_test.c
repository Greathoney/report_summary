#define _CRT_SECURE_NO_WARNINGS
#include "linear_list_array.h"

void printList(List* pList) {
	int i;
	printf("The current status of List: ");
	if (pList->count != 0) {
		for (i = 0; i < pList->count; i++) {
			printf("%d, ", *(int*)pList->data[i]);
		}
		printf("\b\b ");
	}
	printf("\n");
}

int main(void) {
	int menu, value;
	int* pNum;

	List* l1 = createList(5);

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
