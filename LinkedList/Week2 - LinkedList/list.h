#pragma once

struct listNode {
	int data;
	struct listNode *next;
};

typedef struct listNode *ListNodePtr;

struct list {
	ListNodePtr head;
};

typedef struct list List;

//functions

List new_list();
void print_list(List *self);
void insert_at_front(List *self, int data);
void insert_in_order(List *self, int data);
void delete_from_list(List *self, int data);
void destroy_list(List *self);