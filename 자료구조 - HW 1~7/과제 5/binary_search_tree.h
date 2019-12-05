#include <stdio.h>
#include <malloc.h>
typedef enum { false, true } bool;

typedef char* Element;

typedef struct tTreeNode {
	Element data;
	struct tTreeNode* left, * right;
}TreeNode;

//dict order
int compareElement(Element text1, Element text2) { //same: 0 text1: 1 text2: 2
	int i;

	for (i = 0; text1[i] != '\0' || text2[i] != '\0'; i++) {
		if (text1[i] > text2[i]) {
			return 1;
		}
		else if (text1[i] < text2[i]) {
			return 2;
		}
	}

	if (text1[i] == '\0' && text2[i] == '\0') {
		return 0;
	}
	else if (text1[i] == '\0') {
		return 2;
	}
	else if (text2[i] == '\0') {
		return 1;
	}
	return -1;
}

TreeNode* CreateTree(Element item) {
	TreeNode* pNewNode = (TreeNode*)malloc(sizeof(TreeNode));

	pNewNode->data = item;
	pNewNode->left = NULL;
	pNewNode->right = NULL;

	return pNewNode;
}

void DestroyALLTree(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	if (root->left) {
		DestroyALLTree(root->left);
	}
	if (root->right) {
		DestroyALLTree(root->right);
	}
	free(root);
}

TreeNode* findMinNode(TreeNode* root)
{
	TreeNode* tmp = root;
	while (tmp->left != NULL)
		tmp = tmp->left;
	return tmp;
}


TreeNode* BST_delete(TreeNode* root, Element value)
{
	TreeNode* tNode = NULL;
	if (root == NULL)
		return NULL;

	if (compareElement(root->data, value) == 1)
		root->left = BST_delete(root->left, value);
	else if (compareElement(root->data, value) == 2)
		root->right = BST_delete(root->right, value);
	else
	{
		// 자식 노드가 둘 다 있을 경우
		if (root->right != NULL && root->left != NULL)
		{
			tNode = findMinNode(root->right);
			root->data = tNode->data;
			root->right = BST_delete(root->right, tNode->data);
		}
		else
		{
			tNode = (root->left == NULL) ? root->right : root->left;
			free(root);
			return tNode;
		}
	}

	return root;
}

TreeNode* searchTree(TreeNode* tree, Element text) {
	if (!tree) {
		return NULL;
	}

	switch (compareElement(tree->data, text)) {
	case 0:
		return tree;
	case 1:
		return searchTree(tree->left, text);
	case 2:
		return searchTree(tree->right, text);
	}
	return NULL;
}

TreeNode* searchBeforeTree(TreeNode* beforeTree, TreeNode* tree, Element text) {

	if (!tree) {
		return NULL;
	}

	switch (compareElement(tree->data, text)) {
	case 0:
		return beforeTree;
	case 1:
		return searchBeforeTree(tree, tree->left, text);
	case 2:
		return searchBeforeTree(tree, tree->right, text);
	}
	return NULL;
}

void InsertTree(TreeNode* tree, Element text) {

	switch (compareElement(tree->data, text)) {
	case 0:
		printf("[Warning] Already exists same data.\n");
		break;
	case 1:
		if (tree->left == NULL) {
			tree->left = CreateTree(text);
			return;
		}
		else {
			InsertTree(tree->left, text);
			return;
		}
	case 2:
		if (tree->right == NULL) {
			tree->right = CreateTree(text);
			return;
		}
		else {
			InsertTree(tree->right, text);
			return;
		}
	}
}
