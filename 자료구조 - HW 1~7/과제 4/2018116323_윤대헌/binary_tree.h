#include <stdio.h>
#include <malloc.h>
typedef enum {false, true} bool;

typedef char Element;

typedef struct tTreeNode {
	Element data;
	struct tTreeNode* left, * right;
}TreeNode;


TreeNode* CreateTree(Element item) {
	TreeNode* pNewNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (pNewNode == NULL) {
		printf("Not enough memory.\n");
		return NULL;
	}
	pNewNode->data = item;
	pNewNode->left = NULL;
	pNewNode->right = NULL;

	return pNewNode;
}

void DestroyTree(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	if (root->left) {
		DestroyTree(root->left);
	}
	if (root->right) {
		DestroyTree(root->right);
	}
	free(root);
}
