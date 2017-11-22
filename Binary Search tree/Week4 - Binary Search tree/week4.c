#include "bst.h"
#include<stdio.h>

int main() { 
	BST tree = new_bst(0);
	int quit = 0;
	int data;
	while (quit == 0) {
		printf("0 to quit or Enter some data: ");
		scanf("%d", &data);
		if (data != 0) {
			insert_bst(&tree, data);
		} else { 
			quit = 1;
		} 
	}  
	print_pre_order_bst(&tree);
	printf("\n");
	print_in_order_bst(&tree);
	printf("\n");
	print_post_order_bst(&tree);
	printf("\n");
	print_height(&tree);
}