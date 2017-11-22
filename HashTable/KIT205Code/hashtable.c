#include <stdlib.h>
#include "hashtable.h"

HashTable create_hashtable(int n){
	HashTable newtable;
	// TODO: allocate memory for array and init lists
	//List lists[] = malloc(sizeof(List)*n);
//for (size_t i = 0; i < n; i++)
//	{
//		lists[i] = new_list();
//	}


	newtable.table = malloc(sizeof(List)*n);
	for (size_t i = 0; i < n; i++)
	{
		newtable.table[i] = new_list();
	}

	newtable.size = n;

	return newtable;
}

int hash(char* key, int size){
	unsigned long h = 0; // unsigned long, so that when it wraps it's still positive
	int n = strlen(key);

	for (int i = 0; i < n; i++){
		// multiply by 32 (<<5) and add ascii value
		h = (h << 5) + (int)(key[i]);
	}
	return h%size;
}

void hash_insert(HashTable *self, char* key){
	// TODO
	int list_number = hash(key, self->size);
	insert_at_front(&self->table[list_number], key);

}

void hash_remove(HashTable *self, char* key){
	// TODO
	int list_number = hash(key, self->size);
	delete_list(&self->table[list_number], key);
}

void hash_print(HashTable *self){
	for (int i = 0; i < self->size; i++){
		printf("%d: ", i);
		print_list(&(self->table[i]));
	}
}

void hash_destroy(HashTable *self){
	// TODO
	for (size_t i = 0; i < self->size; i++)
	{
		destroy_list(&self->table[i]);
	}
}