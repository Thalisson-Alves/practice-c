#include <stdbool.h>

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

struct Item{
	char *key;
	char *value;
	struct Item *next;
};

typedef struct HashTable{
	struct Item **data;
	int size;
}hash_table;

// Test whether the memory was successfully allocated
void check_address(void *ptr);
// hash a string into an integer in range 0 to size-1
int hash(char *key, int size);
// constructor
hash_table *hash_table_new(int size);
// destructor
void hash_table_destroy(hash_table *table);
// add an item
void hash_table_add(hash_table *table, char *key, char *value);
// return true if the given key exists else return false
bool hash_table_exists(hash_table *table, char *key);
// return the value of the given key if the key exists else return null character '\0'
const char *hash_table_get(hash_table *table, char *key);
// remove a key if the given key exists else do nothing
void hash_table_remove(hash_table *table, char *key);


/*==== IMPLEMENTATION ====*/

void check_address(void *ptr){
	if(!ptr){
		printf("Bad allocation.\n");
		exit(EXIT_FAILURE);
	}
}

int hash(char *key, int size){
	unsigned hashed = 0;
	for(int i=0; key[i] != '\0'; i++)
		hashed += ((i+1)*key[i])%size;
	return hashed % size;
}

hash_table *hash_table_new(int size){
	hash_table *table = (hash_table *)malloc(sizeof(hash_table));
	check_address(table);
	table->size = size;
	table->data = (struct Item **)malloc(sizeof(struct Item *)*size);
	check_address(table->data);
	for(int i=0; i<size; i++){
		*(table->data+i) = NULL;
	}
	
	return table;
}

void hash_table_destroy(hash_table *table){
	for(int i=0; i<table->size; i++){
		if(*(table->data+i)){
			struct Item *temp = *(table->data+i);
			while(temp){
				struct Item *next = temp->next;
				// free(temp->key);
				// free(temp->value);
				free(temp);
				temp = next;
			}
		}
	}
	free(table->data);
}

void hash_table_add(hash_table *table, char *key, char *value){
	int hashed = hash(key, table->size);
	struct Item *temp = *(table->data+hashed);
	struct Item *last = NULL;
	while(temp){
		bool equal = true;
		int i=0;
		do{
			if(temp->key[i] != key[i]){
				equal = false;
				break;
			}
		}while(key[i++] != '\0');
		// for(int i=0; ; i++){
			// if(temp->key[i] != key[i]){
				// equal = false;
			// }
			// if(key[i] == '\0')
				// break;
		// }
		if(equal){
			temp->value = value;
			return;
		}
		last = temp;
		temp = temp->next;
	}
	struct Item *new_item = (struct Item *)malloc(sizeof(struct Item));
	check_address(new_item);
	new_item->key = key;
	new_item->value = value;
	new_item->next = NULL;
	if(!last){
		*(table->data+hashed) = new_item;
	}
	else{
		last->next = new_item;
	}
}

bool hash_table_exists(hash_table *table, char *key){
	int hashed = hash(key, table->size);
	struct Item *temp = *(table->data+hashed);
	while(temp){
		bool equal = true;
		int i=0;
		do{
			if(key[i] != temp->key[i]){
				equal = false;
			}
		}while(key[i] == '\0');
		if(equal)
			return true;
		temp = temp->next;
	}
	return false;
}

const char *hash_table_get(hash_table *table, char *key){
	int hashed = hash(key, table->size);
	struct Item *temp = *(table->data+hashed);
	while(temp){
		bool equal = true;
		int i=0;
		do{
			if(key[i] != temp->key[i]){
				equal = false;
				break;
			}
		}while(key[i++] != '\0');
		if(equal)
			return temp->value;
		temp = temp->next;
	}
	return "\0";
}

void hash_table_remove(hash_table *table, char *key){
	int hashed = hash(key, table->size);
	struct Item *temp = *(table->data+hashed);
	struct Item *prev = NULL;
	while(temp){
		bool equal = true;
		int i=0;
		do{
			if(key[i] != temp->key[i]){
				equal = false;
				break;
			}
		}while(key[i++] != '\0');
		if(equal){
			struct Item *next = temp->next;
			free(temp);
			if(!prev){
				*(table->data+hashed) = next;
			}
			else{
				prev->next = next;
			}
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

void hash_table_debug(hash_table *table){
	for(int i=0; i<table->size; i++){
		if(*(table->data+i) == NULL)
			printf("NULL");
		else{
			struct Item *temp = *(table->data+i);
			while(temp){
				printf("{key:\"%s\" ", temp->key);
				printf("value:\"%s\"}\t", temp->value);
				temp = temp->next;
			}
		}
		printf("\n");
	}
	printf("--------------------------------------------------------------\n");
}

#endif