#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int list[], int n) {
	int i, j, temp;

	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (list[j] > list[j + 1]) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}


int main(void) {
	int i;
	int listA[200] = { 0, }; //data
	int listA_last = 200;

	for (i = 0; i < 200; i++) {
		listA[i] = rand() % 100;
	}

	printf("Before: ");
	for (i = 0; i < listA_last; i++) {
		printf("%d ", listA[i]);
	}
	printf("\n");

	bubbleSort(listA, listA_last);

	printf("After: ");
	for (i = 0; i < listA_last; i++) {
		printf("%d ", listA[i]);
	}
	printf("\n");
	return 0;
}
