#include <stdio.h>
#include <stdlib.h>
#include "list.h"


List merged_list(List *A, List *B){
	List merged = new_list();
	ListNodePtr curA = A->head;
	ListNodePtr curB = B->head;
	while (curA != NULL && curB != NULL)
	{
		insert_in_order(&merged, curA->data);
		insert_in_order(&merged, curB->data);
		curA = curA->next;
		curB = curB->next;
	}
	return merged;
}

List merge_no_order(List *A, List *B){
	List merged;
	merged.head = NULL;
	ListNodePtr temp = NULL;
	ListNodePtr prev = NULL;
	ListNodePtr curA = A->head;
	ListNodePtr curB = B->head;
	while (curA != NULL && curB != NULL)
	{
		temp = malloc(sizeof *temp);
		temp->data = curA->data;
		if (merged.head == NULL){
			merged.head = temp;
		}
		else
		{
			prev->next = temp;
		}
		temp->next = malloc(sizeof *temp);
		temp = temp->next;
		temp->data = curB->data;
		temp->next = NULL;
		prev = temp;
		//move along
		curA = curA->next;
		curB = curB->next;
	}
	return merged;
}

int main(){
	List listA = new_list();
	List listB = new_list();
	for (size_t i = 1; i < 5; i++)
	{
		insert_in_order(&listA, i);
	}
	for (size_t i = 5; i < 9; i++)
	{
		insert_in_order(&listB, i);
	}
	printf("List A\n");
	print_list(&listA);
	printf("\n");
	printf("List B\n");
	print_list(&listB);
	printf("\n");
	printf("Merged List\n");
	List merged = merged_list(&listA, &listB);
	print_list(&merged);
	printf("\n");
	List merged2 = merge_no_order(&listA, &listB);
	print_list(&merged2);
	printf("\n");
}

