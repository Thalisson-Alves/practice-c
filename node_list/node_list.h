#include <stdbool.h>

#ifndef PROJECT_NODE_LIST_H
#define PROJECT_NODE_LIST_H

typedef struct Node_list_implementation{
	int data;
	struct Node_list_implementation *next;
} Tnode_list;

// ==== Constructor ====
Tnode_list *tnode_list_new();

// ==== Destructor ====
void tnode_list_destroy(Tnode_list *head);

// ==== Element Access ====
int tnode_list_front(Tnode_list *head);
int tnode_list_back(Tnode_list *head);
int tnode_list_value_n_from_end(Tnode_list *head, int n);
int tnode_list_value_at(Tnode_list *head, int index);

// ==== Capacity ====
int tnode_list_size(Tnode_list *head);
bool tnode_list_empty(Tnode_list *head);

// ==== Modifiers ====
void tnode_list_push_front(Tnode_list **head, int value);
void tnode_list_pop_front(Tnode_list **head);
void tnode_list_push_back(Tnode_list **head, int value);
void tnode_list_pop_back(Tnode_list **head);
void tnode_list_insert(Tnode_list **head, int index, int value);
void tnode_list_erase(Tnode_list **head, int index);
void tnode_list_reverse(Tnode_list **head);
void tnode_list_remove_value(Tnode_list **head, int value);

// ==== tests ====
void check_address(void *ptr);
void tnode_list_debug(Tnode_list *head);

#endif