#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void option_insert(List *mylist) {
	printf("\nEnter a value to insert >");
	int value;
	scanf("%d", &value);
	insert_in_order(mylist, value);
}

void option_delete(List *mylist) {
	printf("\nEnter a value to delete >");
	int value;
	scanf("%d", &value);
	delete_from_list(mylist, value);
}

void option_print(List *mylist) {
	printf("\nCurrent Values in the List:\n");
	print_list(mylist);
}

void reverse_list(List *self) {
	if (self->head == NULL) return; //nothing to reverse
	List temp = new_list();
	ListNodePtr current = self->head;
	while (current!=NULL)
	{
		insert_at_front(&temp, current->data);
		current = current->next;
	}
	destroy_list(self);
	*self = temp;
}

List merge_lists(List *list1, List *list2) {
	//to start reverse them both
	List merged = new_list();
	ListNodePtr l1_current = list1->head;
	ListNodePtr l2_current = list2->head;
	while (!(l1_current == NULL && l2_current == NULL)) //while one of them is not null
	{
		if (l2_current==NULL || l1_current->data < l2_current->data) {
			//if smaller or the other one is NULL insert it
			insert_at_front(&merged, l1_current->data);
			l1_current = l1_current->next;
		}
		else
		{
			//its same or bigger insert the other one instead
			insert_at_front(&merged, l2_current->data);
			l2_current = l2_current->next;
		}
	}
	//will result in the wrong order so revese it now
	reverse_list(&merged);
	return merged;
}

void merge_lists_test(){
	List list_of_threes = new_list();
	for (int i = 3; i < 20; i+=3)
	{
		insert_in_order(&list_of_threes, i);
	}
	printf("List of threes:\n");
	print_list(&list_of_threes);

	List list_of_fives = new_list();
	for (int i = 5; i < 20; i += 5)
	{
		insert_in_order(&list_of_fives, i);
	}
	printf("List of fives:\n");
	print_list(&list_of_fives);

	List list_of_both = merge_lists(&list_of_threes, &list_of_fives);
	printf("Both lists as one:\n");
	print_list(&list_of_both);
}





void main() {
	printf("hello world\n");

	List MyList = new_list();

	int option = 0;
	int quit = 0;
	
	while (!quit)
	{
		//show the menu
		printf("Options:\n 0 - Quit\n 1 - Insert Value\n 2 - Delete Value\n 3 - Print Values\n");
		printf(" 4 - reverse the list\n");
		printf(" 5 - Mege List Test\n");
		printf("\n Make a choice > ");
		scanf("%d", &option);

		//process selected option
		switch (option)
		{
		case 0:
			quit = 1;
			break;

		case 1:
			//insert
			option_insert(&MyList);
			break;

		case 2:
			//delete
			option_delete(&MyList);
			break;

		case 3:
			//print
			option_print(&MyList);
			break;

		case 4:
			//reverse
			reverse_list(&MyList);
			break;

		case 5:
			//merge test
			merge_lists_test();
			break;

		default:
			printf("\n*** Invalid option ***\n");
			break;
		}
	}
}

