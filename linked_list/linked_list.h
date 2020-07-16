#include <stdbool.h>

#ifndef PROJECT_LINKED_LIST_H
#define PROJECT_LINKED_LIST_H

struct Single_node{
	int data;
	struct Single_node *next;
};

typedef struct Tlinked_list_implementation{
	struct Single_node *head;
	struct Single_node *tail;
} Tlinked_list;

// ==== Constructor ====
Tlinked_list *tlinked_list_new();

// ==== Destructor ====
void tlinked_list_destroy(Tlinked_list *tlist);

// ==== Element Access ====
int tlinked_list_front(Tlinked_list *tlist);
int tlinked_list_back(Tlinked_list *tlist);
int tlinked_list_value_n_from_end(Tlinked_list *tlist, int n);
int tlinked_list_value_at(Tlinked_list *tlist, int index);

// ==== Capacity ====
int tlinked_list_size(Tlinked_list *tlist);
bool tlinked_list_empty(Tlinked_list *tlist);

// ==== Modifiers ====
void tlinked_list_push_front(Tlinked_list *tlist, int value);
void tlinked_list_pop_front(Tlinked_list *tlist);
void tlinked_list_push_back(Tlinked_list *tlist, int value);
void tlinked_list_pop_back(Tlinked_list *tlist);
void tlinked_list_insert(Tlinked_list *tlist, int index, int value);
void tlinked_list_erase(Tlinked_list *tlist, int index);
void tlinked_list_reverse(Tlinked_list *tlist);
void tlinked_list_remove_value(Tlinked_list *tlist, int value);

// ==== tests ====
void check_address(void *ptr);
void tlinked_list_debug(Tlinked_list *tlist);

#endif