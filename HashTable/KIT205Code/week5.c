#include "list.h"
#include "hashtable.h"
#include <stdio.h>

int main(){
	int command = 1;
	HashTable table = create_hashtable(11);
	char buffer[100];

	while (command){
		printf("Enter an option 0=quit, 1=insert, 2=delete, 3=print\n");
		scanf("%d", &command);
		switch (command){
		case 0:
			command = 0;
			break;
		case 1:
			printf("Enter a string\n");
			scanf("%s", buffer);
			hash_insert(&table, buffer);
			hash_print(&table);
			break;
		case 2: // TODO: remove
			printf("Enter a string\n");
			scanf("%s", buffer);
			hash_remove(&table, buffer);
			hash_print(&table);
			break;
		case 3: // TODO: print
			hash_print(&table);
			break;
		}
		printf("\n");
	}
	// TODO: destroy
	hash_destroy(&table);
}