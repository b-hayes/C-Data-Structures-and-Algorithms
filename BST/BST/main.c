#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int numberOfOneChildNodes(BST self){
	return countOneChileNodes(self.root);
}

int countOneChileNodes(BSTNodePtr self){
	int count = 0;
	if (self == NULL)
	{
		return count;
	}
	if (self->left == NULL && self->right != NULL){
		count++;
	}
	if (self->left != NULL && self->right == NULL){
		count++;
	}
	count += countOneChileNodes(self->left);
	count += countOneChileNodes(self->right);
	return count;
}


int main(){
	BST cat;
	cat.root = NULL;
	insert_bst(&cat, 14);
	insert_bst(&cat, 8);
	insert_bst(&cat, 6);
	insert_bst(&cat, 16);
	insert_bst(&cat, 10);
	insert_bst(&cat, 21);
	insert_bst(&cat, 5);
	insert_bst(&cat, 22);
	insert_bst(&cat, 23);

	print_in_order_bst(&cat);
	printf("\n Nodes with 1 child : %d\n", numberOfOneChildNodes(cat));
}