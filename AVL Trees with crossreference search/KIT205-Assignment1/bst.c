#include "bst.h"
#include <stdlib.h>

TaxRecordPtr new_taxRecord(TaxRecordPtr self, char * name, long tfn) {
	self = malloc(sizeof(*self));
	int leangth = strlen(name);
	self->name = malloc(sizeof(char)*(leangth + 1));
	strcpy(self->name, name);
	self->tfn = tfn;
	self->welfare = new_list();
	self->tax = new_list();
	return self;
}

void add_tax_year(BSTNodePtr self, int year) {
	if (self==NULL)
	{
		printf("**ERROR** Cant add TAX year to record that doesnt exist.\n");
		return;
	}
	insert_at_front(&self->data->tax, year);
}

void add_welfare_year(BSTNodePtr self, int year) {
	if (self == NULL)
	{
		printf("**ERROR** Cant add WELFARE year to record that doesnt exist.\n");
		return;
	}
	insert_at_front(&self->data->welfare, year);
}

BST new_bst() {
	BST temp;
	temp.root = NULL;
	return temp;
}

BSTNodePtr find_bst_node(BSTNodePtr self, long tfn) {
	if (self == NULL || (tfn == self->data->tfn)) {
		return self;
	}
	else if (tfn < self->data->tfn) {
		return find_bst_node(self->left, tfn);
	}
	else {
		return find_bst_node(self->right, tfn);
	}
}

BSTNodePtr find_bst(BST *self, long tfn) {
	return find_bst_node(self->root, tfn);
}


BSTNodePtr insert_bst_node(BSTNodePtr self, long tfn, char * name) {
	if (self == NULL) {
		self = malloc(sizeof *self);
		self->data = new_taxRecord(&self->data, name, tfn);
		self->left = self->right = NULL;
	} else if (tfn < self->data->tfn) {
		self->left = insert_bst_node(self->left, tfn, name);
	} else if (tfn >self->data->tfn) {
		self->right = insert_bst_node(self->right, tfn, name);
	}
	return self; 
}

void insert_bst(BST *self, long tfn, char * name) {
	self->root = insert_bst_node(self->root, tfn, name);
}


void print_pre_order_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		printf("%ld\n", self->data->tfn);
		printf("%s\n", self->data->name);
		printf("Welfare years: ");
		print_list(&self->data->welfare);
		printf("\n");
		printf("Tax years: ");
		print_list(&self->data->tax);
		printf("\n\n");
		print_pre_order_bst_node(self->left);
		print_pre_order_bst_node(self->right);
	}
}

void print_pre_order_bst(BST *self) {
	print_pre_order_bst_node(self->root);
}

void delete_all_bst_nodes(BSTNodePtr self) {
	if (self != NULL) {
		delete_all_bst_nodes(self->left);
		delete_all_bst_nodes(self->right);
		
		free(self->data->name);
		destroy_list(&self->data->tax);
		destroy_list(&self->data->welfare);
		free(self->data);
		free(self);
	}
}

void destroy_bst(BST *self) {
	delete_all_bst_nodes(self->root);
	free(self);
}

void print_comparison(BSTNodePtr self) {
	if (self==NULL)
	{
		printf("No entry with that tax file number\n");
		return;
	}

	ListNodePtr cur_tax = self->data->tax.head;
	ListNodePtr cur_welfare = self->data->welfare.head;

	printf("%s", self->data->name);

	while (cur_welfare != NULL && cur_tax != NULL)
	{
		if (cur_welfare->data == cur_tax->data)
		{
			printf(" %d", cur_welfare->data);
			cur_tax = cur_tax->next;
			cur_welfare = cur_welfare->next;
		}
		else if (cur_welfare->data > cur_tax->data)
		{
			cur_welfare = cur_welfare->next;
		}
		else
		{
			cur_tax = cur_tax->next;
		}
	}
	printf("\n\n");
}