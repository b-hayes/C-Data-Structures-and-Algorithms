#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

BSTNodePtr unbalanced_parent = NULL;
BSTNodePtr unbalanced_node = NULL;
BSTNodePtr unbalanced_child = NULL;
BSTNodePtr unbalanced_grandchild = NULL;

int unbalanced(BSTNodePtr self) {
	int dif = height(self->left) - height(self->right);
	dif = abs(dif);
	if (dif > 1)
	{
		return 1;
	}
	return 0;
}

int height(BSTNodePtr self) {
	int level = 0;
	if (self != NULL) {
		level++;
		int left_level = height(self->left);
		int right_level = height(self->right);
		level += (left_level > right_level) ? left_level : right_level;
	}
	return level;
}

BSTNodePtr insert_avl_node(BSTNodePtr self, long tfn, char * name) {
	if (self == NULL) {
		self = malloc(sizeof *self);
		self->data = new_taxRecord(&self->data, name, tfn);
		self->left = self->right = NULL;
	}
	else if (tfn < self->data->tfn) {
		self->left = insert_avl_node(self->left, tfn, name);
	}
	else if (tfn >self->data->tfn) {
		self->right = insert_avl_node(self->right, tfn, name);
	}
	if (unbalanced_node)
	{
		//there was an unbalanced node found check if we are at the parent of it now
		if (self->left == unbalanced_node || self->right == unbalanced_node)
		{
			unbalanced_parent = self;
		}
	}
	if (unbalanced(self) && unbalanced_node == NULL)
	{
		//this node is unbalanced and there is no unbalanced node yet.
		unbalanced_node = self;
	}
	return self;
}

BSTNodePtr highest_child(BSTNodePtr unbal) {
	if (height(unbal->left) > height(unbal->right))
	{
		return unbal->left;
	}
	return unbal->right;
}

void rotate_right(BSTNodePtr pivot, BSTNodePtr child, BSTNodePtr parent) {
	if (parent)
	{
		if (parent->right == pivot)
		{
			parent->right = child;
		}
		else
		{
			parent->left = child;
		}
	}
	pivot->left = child->right;
	child->right = pivot;
}

void rotate_left(BSTNodePtr pivot, BSTNodePtr child, BSTNodePtr parent) {
	if (parent)
	{
		if (parent->right == pivot)
		{
			parent->right = child;
		}
		else
		{
			parent->left = child;
		}
	}
	pivot->right = child->left;
	child->left = pivot;
}

void insert_avl(BST *self, long tfn, char * name) {
	self->root = insert_avl_node(self->root, tfn, name);
	if (unbalanced_node)
	{
		unbalanced_child = highest_child(unbalanced_node);
		unbalanced_grandchild = highest_child(unbalanced_child);

		if (unbalanced_node->left == unbalanced_child && unbalanced_child->left == unbalanced_grandchild)
		{
			rotate_right(unbalanced_node, unbalanced_child, unbalanced_parent);
			if (unbalanced_parent == NULL)
			{
				self->root = unbalanced_child;
			}
		}
		if (unbalanced_node->right == unbalanced_child && unbalanced_child->right == unbalanced_grandchild)
		{
			rotate_left(unbalanced_node, unbalanced_child, unbalanced_parent);
			if (unbalanced_parent == NULL)
			{
				self->root = unbalanced_child;
			}
		}
		if (unbalanced_node->left == unbalanced_child && unbalanced_child->right == unbalanced_grandchild)
		{
			rotate_left(unbalanced_child, unbalanced_grandchild, unbalanced_node);
			rotate_right(unbalanced_node, unbalanced_grandchild, unbalanced_parent);
			if (unbalanced_parent == NULL)
			{
				self->root = unbalanced_grandchild;
			}
		}
		if (unbalanced_node->right ==  unbalanced_child && unbalanced_child->left == unbalanced_grandchild)
		{
			rotate_right(unbalanced_child, unbalanced_grandchild, unbalanced_node);
			rotate_left(unbalanced_node,unbalanced_grandchild,unbalanced_parent);
			if (unbalanced_parent == NULL)
			{
				self->root = unbalanced_grandchild;
			}
		}
	}
	//reset variables for next time
	unbalanced_parent = NULL;
	unbalanced_node = NULL;
	unbalanced_child = NULL;
	unbalanced_grandchild = NULL;
}

void balance_check_node(BSTNodePtr self) {
	if (self != NULL)
	{
		if (unbalanced(self))
		{
			printf("\nUnbalanced node with TFN: %ld\n", self->data->tfn);
			unbalanced_node = self;
		}
		balance_check_node(self->left);
		balance_check_node(self->right);
	}
}

void balance_check(BST * self) {
	balance_check_node(self->root);
	if (unbalanced_node == NULL)
	{
		printf("\nAll nodes are balanced.\n");
	}
	unbalanced_node = NULL;
}