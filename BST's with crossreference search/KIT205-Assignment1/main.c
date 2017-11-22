#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

void print_file(char * filename) {

	int num_records, num_years, year;
	char name[30];
	long tfn;

	FILE *filePtr;
	filePtr = fopen(filename, "r");
	fscanf(filePtr, "%d", &num_records);
	printf("===================[ %s has %d records ]==================\n", filename, num_records);

	for (size_t i = 0; i < num_records; i++)
	{
		if (strcmp(filename, "welfare1.txt")==0)
		{
			fscanf(filePtr, "%s", name);
			printf("%s\n", name);
		}

		fscanf(filePtr, "%d", &tfn);
		printf("%d\n", tfn);

		fscanf(filePtr, "%d", &num_years);
		printf("%d", num_years);

		for (size_t i = 0; i < num_years; i++)
		{
			fscanf(filePtr, "%d", &year);
			printf(" %d", year);
		}
		printf("\n");
	}
	printf("===============================================================\n");
}

void show_menu() {
	printf("==========[ Menu Options ]============\n");
	printf(" 0 to quit.\n");
	printf(" 1 to print all Wellfair file.\n");
	printf(" 2 to print all tax file.\n");
	printf(" 3 to print the BST.\n");
	printf(" Enter a TFN to check matching years.\n");
	printf("======================================\n");
	printf("Enter Numbers only >");
}



void populate_tree(BST * self) {
	int num_records, num_years, year;
	char name[30];
	long tfn;
	BSTNodePtr to_add_year_to;
	int ignore_count = 0;

	FILE *filePtr;
	filePtr = fopen("welfare1.txt", "r");

	fscanf(filePtr, "%d", &num_records);
	
	for (size_t i = 0; i < num_records; i++)
	{		
		fscanf(filePtr, "%s", name);
		fscanf(filePtr, "%d", &tfn);
		insert_bst(self, tfn, name);

		to_add_year_to = find_bst(self, tfn);
		
		fscanf(filePtr, "%d", &num_years);

		for (size_t i = 0; i < num_years; i++)
		{
			fscanf(filePtr, "%d", &year);
			add_welfare_year(to_add_year_to, year);
		}
	}


	filePtr = fopen("tax1.txt", "r");

	fscanf(filePtr, "%d", &num_records);

	for (size_t i = 0; i < num_records; i++)
	{
		fscanf(filePtr, "%d", &tfn);

		to_add_year_to = find_bst(self, tfn);
		if (to_add_year_to == NULL) ignore_count++;

		fscanf(filePtr, "%d", &num_years);

		for (size_t i = 0; i < num_years; i++)
		{
			fscanf(filePtr, "%d", &year);
			if (to_add_year_to != NULL)
			{
				add_tax_year(to_add_year_to, year);
			}
		}
	}
	printf("%d TAX records ignored since they have no welfare info.\n\n", ignore_count);
}

void main() {
	int quit = 0;
	long option;
	BST tree = new_bst(0);
	populate_tree(&tree);

	while (!quit)
	{
		//show_menu();
		scanf("%ld", &option);

		switch (option)
		{
		case 0:
			quit = 1;
			break;

		case 1:
			print_file("welfare1.txt");
			break;

		case 2:
			print_file("tax1.txt");
			break;

		case 3:
			print_pre_order_bst(&tree);
			break;
		default:
			print_comparison(find_bst(&tree, option));
			break;
		}
	}

	
}