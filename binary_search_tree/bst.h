#include <stdbool.h>

#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

typedef struct BST_node
{
	int data;
	struct BST_node *left;
	struct BST_node *right;
} BST;

/* PROTOTIPE */

// allocate a new node
BST *bst_newNode(int value);
// allocate and insert a new node in the tree if the value isnt already there
void bst_insert(BST **root, int value);
// return true if tree is empty
bool bst_empty(BST *root);
// return the quantity of values
int bst_size(BST *root);
// print values from min to max
void bst_print(BST *root);
// destructor
// delete all nodes in the tree freeing their memory
void bst_destroy(BST *root);
// reset the tree freeing all nodes, so it doesnt crash if you keep using the same tree
void bst_clear(BST **root);
// return true if the given value exists in the tree
bool bst_exists(BST *root, int value);
// return height of the tree
int bst_height(BST *root);
// return the min value, -1 if none
int bst_min(BST *root);
// return the max value, -1 if none
int bst_max(BST *root);
// delete the given value
void bst_deleteValue(BST **root, int value);
// return the next-highest value in tree after given value, -1 if none
int bst_nextHighest(BST *root, int value);
// return the next-smaller value in tree after given value, -1 if none
int bst_nextSmaller(BST *root, int value);


/* IMPLEMENTATION */

BST *bst_newNode(int value)
{
	// allocate a new node
	BST *node = (BST *)malloc(sizeof(BST));
	
	// check the address
	if (!node)
	{
		printf("Bad allocation\n");
		exit(EXIT_FAILURE);
	}
	
	// initialize the node
	node->data = value;
	node->right = NULL;
	node->left = NULL;
	
	return node;
}

void bst_insert(BST **root, int value)
{
	BST *current = *root;
	if (!current)
		*root = bst_newNode(value);
	else if(current->data < value)
		bst_insert(&current->right, value);
	else if (current->data > value)
		bst_insert(&current->left, value);
	else
		return;
}

bool bst_empty(BST *root) {return !root; }

int bst_size(BST *root)
{
	if (!root)
		return 0;
	return 1 + bst_size(root->left) + bst_size(root->right);
}

void bst_print(BST *root)
{
	if (!root)
		return;
	bst_print(root->left);
	printf("%i\n", root->data);
	bst_print(root->right);
}

void bst_destroy(BST *root)
{
	if (!root)
		return;
	bst_destroy(root->left);
	bst_destroy(root->right);
	free(root);
}

void bst_clear(BST **root)
{
	// freeing the memory
	bst_destroy(*root);
	// restarting the root
	*root = NULL;
}

bool bst_exists(BST *root, int value)
{
	if (!root)
		return false;
	if (root->data < value)
		return bst_exists(root->right, value);
	if (root->data > value)
		return bst_exists(root->left, value);
	return true;
}

// used to calculate the height
int max_value(int a, int b)
{
	return a > b ? a : b;
}

int bst_height(BST *root)
{
	if (!root)
		return 0;
	return 1 + max_value(bst_height(root->left), bst_height(root->right));
}

int bst_min(BST *root)
{
	if (!root)
		return -1;
	while (root->left) {
		root = root->left;
	}
	return root->data;
}

int bst_max(BST *root)
{
	if (!root) 
		return -1;
	while (root->right)
		root = root->right;
	
	return root->data;
}

// trying to keep it a little bit more balanced
void bst_deleteValue(BST **root, int value)
{
	BST *node = *root;
	if (!node)
		return;
	
	if (node->data < value)
		bst_deleteValue(&node->right, value);
	if (node->data > value)
		bst_deleteValue(&node->left, value);
	// found
	if (node->data == value) {
		int rightHeight = bst_height(node->right);
		int leftHeight = bst_height(node->left);
		// right height is less than left height
		if (rightHeight < leftHeight) {
			// left side becomes parent of the right side
			*root = node->left;
			BST *tmp = *root;
			while (tmp->right) {
				tmp = tmp->right;
			}
			tmp->right = node->right;
		}
		// left height is less or equal to right height
		else if (rightHeight && leftHeight <= rightHeight) {
			// right side becomes parent of the left side
			*root = node->right;
			BST *tmp = *root;
			while (tmp->left)
				tmp = tmp->left;
			tmp->left = node->left;
		}
		// node to be deletede is a leaf
		else {
			*root = NULL;
		}
		free(node);
	}
}

int bst_nextHighest(BST *root, int value)
{
	if (!root)
		return -1;
	if (root->data <= value)
		return bst_nextHighest(root->right, value);
	else {
		while (root->left)
			root = root->left;
		return root->data;
	}
}

int bst_nextSmaller(BST *root, int value)
{
	if (!root)
		return -1;
	if (root->data >= value)
		return bst_nextSmaller(root->left, value);
	else {
		while (root->right)
			root = root->right;
		return root->data;
	}
}

#endif