#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// hash function maked by rand, input is seed.
// Collision: if same index, next rand(seed) sequence
int hashFunction(int num, int repeat) {
	int i;
	srand((unsigned int)num);

	for (i = 0; i < repeat; i++) {
		rand();
	}

	return rand() % 100;
}

int main(void) {
	int menu, i, num;
	int nArray[100] = { 0, };
	while (1) {
		printf("1) insert, 2)search, 3)exit. : ");
		scanf("%d", &menu);

		switch (menu) {
		case 1:
			printf("Input to insert.(Except Zero) : ");
			scanf("%d", &num);

			for (i = 0; nArray[hashFunction(num, i)] != 0; i++) {
			}

			nArray[hashFunction(num, i)] = num;
			break;

		case 2:
			printf("Input to search. : ");
			scanf("%d", &num);

			if (nArray[hashFunction(num, 0)] == 0) {
				printf("there's no %d", num);
			}
			for (i = 1; nArray[hashFunction(num, i)] != num && i < 201; i++) {
			}
			if (i == 201) {
				printf("there's no %d", num);
			}
			else {
				printf("there's %d", num);
			}
			break;

		case 3:
			printf("Program terminates.\n");
			return 0;

		default:
			printf("Wrong input.\n");

		}
		printf("\n%d, %d\n", i, hashFunction(num, i));
	}
	return -1;
}
