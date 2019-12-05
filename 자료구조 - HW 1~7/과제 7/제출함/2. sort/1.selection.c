#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void selectionSort(int list[], int last) {
	int current, walker;

	int smallest;
	int holdData;

	for (current = 0; current < last; current++) {
		smallest = current;
		for (walker = current + 1; walker <= last; walker++) {
			if (list[walker] < list[smallest]) {
				smallest = walker;
			}
		}
		holdData = list[current];
		list[current] = list[smallest];
		list[smallest] = holdData;
	}
	return;
}


int main(void) {
	int i;
	int listA[200] = { 0, }; //data
	int listA_last = 200;

	for (i = 0; i < 200; i++){
		listA[i] = rand() % 100;
	}

	printf("Before: ");
	for (i = 0; i < listA_last; i++) {
		printf("%d ", listA[i]);
	}
	printf("\n");

	selectionSort(listA, listA_last);

	printf("After: ");
	for (i = 0; i < listA_last; i++) {
		printf("%d ", listA[i]);
	}
	printf("\n");
	return 0;
}
