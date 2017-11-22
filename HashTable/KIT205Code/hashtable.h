#pragma once

#include "list.h"

typedef struct hashTable{
	int size;
	List *table;
} HashTable;

HashTable create_hashtable(int n);

int hash(char* key, int size);

void hash_insert(HashTable *self, char* key);

void hash_remove(HashTable *self, char* key);

void hash_print(HashTable *self);

void hash_destroy(HashTable *self);