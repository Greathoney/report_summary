// Graphs using adjacency matrix

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define max 20
int n = 0;
int matrix[max][max];

char printed[max];
int printed_index = 0;


void DFT(char standard, int i) {
	int a, x;
	int check = 1;

	for (x = 0; x < printed_index; x++) {
		if (printed[x] == standard + i - 1) {
			check = 0;
			break;
		}
	}
	if (check) {
		printf("%c ", standard + i - 1);
		printed[printed_index++] = standard + i - 1;
	}
	for (a = 1; a <= n; a++) {
		if (matrix[i][a] == 1){
			DFT(standard, a);
		}
	}
}

void BFT(char standard) {
	int i, j, k, check = 1;
	int before_index = 0, before_index2 = 0;

	char print_check[max];
	int print_check_index = 0;

	int oncePrinted = 0;


	print_check[print_check_index++] = standard;

	for (i = 1; i <= n; i++) {
		if (matrix[1][i] == 1) {
			print_check[print_check_index++] = standard + i - 1;
		}
	}

	before_index = 1;
	before_index2 = print_check_index;

	for (i = 1; 1; i++) {
		oncePrinted = 0;
		for (j = before_index; j < before_index2; j++) {
			for (k = 1; k <= n; k++) {
				if (matrix[standard + j - 'A' + 1][k] == 1) {
					print_check[print_check_index++] = standard + k - 1;
					oncePrinted = 1;
				}
			}
		}
		if (!oncePrinted) {
			for (i = 0; i < print_check_index; i++) {
				check = 1;
				for (j = 0; j < printed_index; j++) {
					if (printed[j] == print_check[i]) {
						check = 0;
						break;
					}
				}

				if (check) {
					printf("%c ", print_check[i]);
					printed[printed_index++] = print_check[i];

				}
			}
			return;

		}

		before_index = before_index2;
		before_index2 = print_check_index;
	}
}

int main(void) {
	char standard, input1, input2;
	int i, j;
	int vaild;
	int choice;
	int node;

	//create_graph
	FILE* read_file = fopen("input.txt", "r");
	fscanf(read_file, "%c\n", &standard);

	while (1) {
		vaild = fscanf(read_file, "%c %c\n", &input1, &input2);
		if (vaild != 2) {
			break;
		}
		n++;
		input1 -= standard;
		input2 -= standard;
		matrix[input1 + 1][input2 + 1] = 1;
	}
	fclose(read_file);

	while (1) {
		printf("1. Insert  2. Delete  3. Display Maxtrix  4. Exit  5. Depth-first traversal  6. Breath-first traversal: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			n++;
			for (i = 1; i <= n; i++) {
				matrix[i][n] = 0;
				matrix[n][i] = 0;
			}
			break;
		case 2:
			printf("Enter a node to be deleted: ");
			fflush(stdin); // to delete input buffer
			scanf("%d", &node);
			if (n == 0) {
				printf("Graph is empty.\n");
				break;
			}
			if (node > n) {
				printf("This node is not present in the graph.\n");
				break;
			}
			for (i = node; i <= n - 1; i++) {
				for (j = 1; j <= n; j++) {
					matrix[j][i] = matrix[j][i + 1];
					matrix[i][j] = matrix[i + 1][j];
				}
			}
			n--;
			break;
		case 3:
			printf("    ");
			for (i = 1; i <= n; i++) {
				printf("%4c", standard + i - 1);
			}
			printf("\n");
			for (i = 1; i <= n; i++) {
				printf("%4c", standard + i - 1);
				for (j = 1; j <= n; j++) {
					printf("%4d", matrix[i][j]);
				}
				printf("\n");
			}
			break;
		case 4:
			printf("Program Terminates. \n");
			return 0;

		case 5:
			printed_index = 0;
			DFT(standard, 1);
			printf("\n");
			break;
		case 6:
			printed_index = 0;
			BFT(standard);
			break;

		default:
			printf("Wrong choice. \n");
			break;
		}
		printf("\n");
	}
	return -1;
}
