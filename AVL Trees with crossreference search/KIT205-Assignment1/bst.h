#pragma once
#include "list.h"

typedef struct taxRecord {
	long tfn;
	char *name;
	List welfare;
	List tax;
} *TaxRecordPtr;

typedef struct bstNode {
	TaxRecordPtr data;
	struct bstNode *left;
	struct bstNode *right;
} *BSTNodePtr;

typedef struct bst {
	BSTNodePtr root;
} BST;

BSTNodePtr find_bst(BST *self, long tfn);
void insert_bst(BST *self, long tfn, char * name);
void print_pre_order_bst(BST *self);
BST new_bst();
void add_welfare_year(BSTNodePtr self, int year);
void add_tax_year(BSTNodePtr self, int year);
void print_comparison(BSTNodePtr self);
void destroy_bst(BST *self);