#include "bst.h"
#include <stdlib.h>
#include <math.h>

BST new_bst(int wtf) {
	BST temp;
	temp.root = NULL;
	return temp;
	
}

//searching
BSTNodePtr find_bst_node(BSTNodePtr self, int n) {
	if (self == NULL || (n == self->data_item)) {
		return self;
	}
	else if (n < self->data_item) {
		return find_bst_node(self->left, n);
	}
	else {
		return find_bst_node(self->right, n);
	}
}

BSTNodePtr find_bst(BST *self, int n) {
	return find_bst_node(self->root, n);
}


//Inserting Into a BST
BSTNodePtr insert_bst_node(BSTNodePtr self, int n) {
	if (self == NULL) {
		/* found where to put it*/
		self = malloc(sizeof *self);
		self->data_item = n;
		self->left = self->right = NULL;
	} else if (n < self->data_item) {
		self->left = insert_bst_node(self->left, n);
	} else if (n >self->data_item) {
		self->right = insert_bst_node(self->right, n);
	}
	return self; 
}

void insert_bst(BST *self, int n) {
	self->root = insert_bst_node(self->root, n);
}

//find min node (used in delete)
BSTNodePtr min_node(BSTNodePtr self) {
	BSTNodePtr current = self;
	while (current->left != NULL) {
		current = current->left;
	} 
	return current;
}

//delete
BSTNodePtr delete_bst_node(BSTNodePtr self, int n) {
	if (self != NULL) {
		if (n == self->data_item) {
			// found item 
			if (self->left != NULL && self->right != NULL) {
				// two child case 
				BSTNodePtr successor = min_node(self->right);
				self->data_item = successor->data_item;
				self->right = delete_bst_node(self->right, self->data_item);
			} else { 
				// one or zero child case
				BSTNodePtr to_free = self;
				if (self->left) { self = self->left;
				} else {
					self = self->right;
				} free(to_free);
			}
		}
		else if (n < self->data_item) {
			self->left = delete_bst_node(self->left, n);
		}
		else {
			self->right = delete_bst_node(self->right, n);
		}
	} 
	return self;
}

//wrapper for delete so that users dont have to worry about the return value
void delete_bst(BST *self, int n) {
	self->root = delete_bst_node(self->root, n);
}

//print self then recuse on left child then recurse on right child
void print_pre_order_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		printf("(");
		printf(" %d ", self->data_item);
		print_pre_order_bst_node(self->left);
		print_pre_order_bst_node(self->right);
		printf(")");
	} else { 
		printf("_");
	}
}

void print_pre_order_bst(BST *self) {
	print_pre_order_bst_node(self->root);
}

//recurse left child, print self, then recurse right child
void print_in_order_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		printf("(");
		print_in_order_bst_node(self->left);
		printf(" %d ", self->data_item);
		print_in_order_bst_node(self->right);
		printf(")");
	}
	else {
		printf("_");
	}
}

void print_in_order_bst(BST *self) {
	print_in_order_bst_node(self->root);
}

//recurse left child, recurse right child, then print self
void print_post_order_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		printf("(");
		print_post_order_bst_node(self->left);
		print_post_order_bst_node(self->right);
		printf(" %d ", self->data_item);
		printf(")");
	}
	else {
		printf("_");
	}
}

void print_post_order_bst(BST *self) {
	print_post_order_bst_node(self->root);
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

void print_height(BST *self) {
	printf("Tree height = %d\n", height(self->root));
}
