#pragma once

//TODO: change data type to char*

typedef struct listNode {
	char *data;
	struct listNode *next;
} *ListNodePtr;

typedef struct list {
	ListNodePtr head;
} List;

void print_list(List *self);

void insert_at_front(List *self, int data);

void delete_list(List *self, int data);

void destroy_list(List *self);

List new_list();