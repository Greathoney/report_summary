#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void insertionSort(int list[], int last) {
	int hold;
	int walker;

	int i;

	for (i = 1; i <= last; i++) {
		if (list[i] == 0) {
			continue;
		}
		hold = list[i];
		for (walker = i - 1; walker >= 0 && hold < list[walker]; walker--) {
			list[walker + 1] = list[walker];
		}
		list[walker + 1] = hold;
	}
	return;
}


int main(void) {
	int i, menu, num;
	int listA[200] = { 0, }; //data
	int listA_last = 0;

	while (1) {
		printf("1) insert, 2)print, 3)exit. : ");
		scanf("%d", &menu);

		switch (menu) {
		case 1:
			printf("Input to insert.(except zero) : ");
			scanf("%d", &num);
			listA[listA_last++] = num;
			insertionSort(listA, listA_last);
			break;

		case 2:
			for (i = 0; i < listA_last; i++) {
				printf("%d ", listA[i]);
			}
			break;

		case 3:
			printf("Program terminates.\n");
			return 0;

		default:
			printf("Wrong input.\n");

		}
		printf("\n");
	}
	return -1;
}
