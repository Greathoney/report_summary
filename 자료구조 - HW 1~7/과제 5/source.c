#define _CRT_SECURE_NO_WARNINGS
#include "binary_search_tree.h"


void Preorder_print(TreeNode* tree) {
	printf("%s ", tree->data);
	if (tree->left != NULL) {
		Preorder_print(tree->left);
	}
	if (tree->right != NULL) {
		Preorder_print(tree->right);
	}
}

void Inorder_print(TreeNode* tree) {
	if (tree->left != NULL) {
		Inorder_print(tree->left);
	}

	printf("%s ", tree->data);

	if (tree->right != NULL) {
		Inorder_print(tree->right);
	}
}

void Postorder_print(TreeNode* tree) {
	if (tree->left != NULL) {
		Postorder_print(tree->left);
	}

	if (tree->right != NULL) {
		Postorder_print(tree->right);
	}
	printf("%s ", tree->data);
}

void Breath_first_print(TreeNode* tree) {
	int i, j;
	int before_index, before_index2;
	TreeNode* nodes[100];
	int nodes_index = 0;
	
	bool oncePrinted = false;

	printf("%s ", tree->data);
	before_index = 0;
	nodes[nodes_index++] = tree->left;
	nodes[nodes_index++] = tree->right;
	before_index2 = nodes_index;
	
	for (i = 1; 1; i++){
		oncePrinted = false;
		for (j = before_index; j < before_index2; j++) {
			if (nodes[j] == NULL) {
				continue;
			}
			printf("%s ", nodes[j]->data);
			nodes[nodes_index++] = nodes[j]->left;
			nodes[nodes_index++] = nodes[j]->right;
			oncePrinted = true;
		}
		if (!oncePrinted) {
			return;
		}
		before_index = before_index2;
		before_index2 = nodes_index;
	}
}

// 문자열의 사전식 순서
int main(void) {
	int menu;
	char* inputText;
	char* searchText = (char*)malloc(sizeof(char) * 100);
	TreeNode* search_Tree = NULL;
	TreeNode* mainTree = NULL;
	TreeNode* search_before_Tree = NULL;

	while (1) {
		printf("0) insert, 1) delete, 2) search, 3) print, 4) exit\n");
		printf("Input menu: ");
		scanf("%d", &menu);

		switch (menu) {
		case 0: //insert
			inputText = (char*)malloc(sizeof(char) * 100);
			printf("Input text: ");
			scanf("%s", inputText); //띄어쓰기는 허용 x

			if (mainTree == NULL) {
				mainTree = CreateTree(inputText);
			}
			else {
				InsertTree(mainTree, inputText);
			}
			break;

		case 1: //delete
			printf("Delete text: ");
			scanf("%s", searchText);

			mainTree = BST_delete(mainTree, searchText);
			break;

		case 2: //search
			printf("Search text: ");
			scanf("%s", searchText);

			search_Tree = searchTree(mainTree, searchText);
			if (search_Tree != NULL) {
				printf("There's data.\n");
			}
			else {
				printf("There's no data.\n");
			}
			break;

		case 3: //print
			printf("Preorder print: ");
			Preorder_print(mainTree);
			printf("\n");

			printf("Inorder print: ");
			Inorder_print(mainTree);
			printf("\n");

			printf("Postorder print: ");
			Postorder_print(mainTree);
			printf("\n");

			printf("Breadth first print: ");
			Breath_first_print(mainTree);
			printf("\n");

			break;

		case 4: //exit
			DestroyALLTree(mainTree);
			printf("Program Terminates.\n");
			return 0;
		}

		printf("\n");
	}
}
