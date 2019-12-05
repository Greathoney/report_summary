#define _CRT_SECURE_NO_WARNINGS
#include "binary_tree.h"

int int_pow(int n, int c) {
	int i;
	int answer = 1;
	for (i = 0; i < c; i++) {
		answer *= n;
	}
	return answer;
}

void Preorder_print(TreeNode* tree) {
	printf("%c ", tree->data);
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

	printf("%c ", tree->data);

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
	printf("%c ", tree->data);
}

void Breath_first_print(TreeNode* tree, int level) {
	int i, j;
	int before_index, before_index2;
	TreeNode* nodes[100];
	int nodes_index = 0;

	printf("%c ", tree->data);
	before_index = 0;
	nodes[nodes_index++] = tree->left;
	nodes[nodes_index++] = tree->right;
	before_index2 = nodes_index;

	for (i = 1; i < level + 1; i++){
		for (j = before_index; j < before_index2; j++) {
			if (nodes[j] == NULL) {
				return;
			}
			printf("%c ", nodes[j]->data);
		}
		for (j = before_index; j < before_index2; j++) {
			nodes[nodes_index++] = nodes[j]->left;
			nodes[nodes_index++] = nodes[j]->right;
		}
		before_index = before_index2;
		before_index2 = nodes_index;

	}
}

int main(void) {
	int i, j;
	int level = 0, index = 1;

	TreeNode* tree, * treeNode, *newNode;

	char* text = (char*)malloc(sizeof(char) * 100);

	printf("Input text: ");
	scanf("%s", text);

	tree = CreateTree(text[0]);

	for (i = 1; text[i] != '\0'; i++) {
		while (index >= 0) {
			index = i - int_pow(2, ++level) + 1;
		}
		index = i - int_pow(2, --level) + 1;

		newNode = CreateTree(text[i]);
		treeNode = tree;
		for (j = 0; j < level - 1; j++) {
			if (index < int_pow(2, level - j - 1)) {
				treeNode = treeNode->left;
			}
			else {
				treeNode = treeNode->right;
			}
			index %= int_pow(2, level - j - 1);
		}
		if (index < int_pow(2, level - j - 1)) {
			treeNode->left = newNode;
		}
		else {
			treeNode->right = newNode;
		}
	}

	printf("Preorder print: ");
	Preorder_print(tree);
	printf("\n");

	printf("Inorder print: ");
	Inorder_print(tree);
	printf("\n");

	printf("Postorder print: ");
	Postorder_print(tree);
	printf("\n");

	printf("Breadth first print: ");
	Breath_first_print(tree, level);
	printf("\n");

	DestroyTree(tree);
	printf("Successfully Finished.\n");
	return 0;
}
