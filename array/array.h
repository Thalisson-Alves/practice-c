#ifndef PROJECT_ARRAY_H
#define PROJECT_ARRAY_H

#include <assert.h>
#include <stdbool.h>

const int GROWTH_RATE = 2;
const int MIN_CAPACITY = 16;
const int SHRINK_RATE = 4;

typedef struct TArrayStructImplementation{
	int *data;
	int size;
	int capacity;
} Tarray;

// ==== Constructors ====
Tarray *tarray_new();					// Empty array of ints
Tarray *tarray_new_size(int size);		// Inital array size (initialize all the elements with 0)

// ==== Destructor ====
void tarray_destroy(Tarray* a); 		// Deallocate all the storage capacity

// ==== Element access ====
int tarray_back(Tarray *a);				// Access last element
int tarray_front(Tarray *a);			// Access first element
int tarray_at(Tarray* a, int index);	// Access the element at some index
int tarray_find(Tarray *a, int value);  // Return the index of the first occurence

// ==== Capacity ====
int tarray_size(Tarray* a);								// Return size
void tarray_resize_for_size(Tarray *a, int new_size);	// Change the capacity to accomodate the new size 
int tarray_determine_capacity(int size);				// Return the capacity (in power of GROWTH_RATE) to accomodate the given size
int tarray_capacity(Tarray* a);							// Return capacity
bool tarray_empty(Tarray* a);							// Test whether array id empty
void tarray_upsize(Tarray* a);							// Increase the capacity
void tarray_downsize(Tarray* a);						// Decrease the capacity

// ==== Modifiers ====
int tarray_pop(Tarray* a);								// Return the last element and delete it
void tarray_delete(Tarray *a, int index);				// Delete the element of a given index
void tarray_remove(Tarray *a, int value);				// Remove all occurences of an element
void tarray_push(Tarray* a, int n);						// Add an element at the end
void tarray_insert(Tarray* a, int index, int value);	// Insert an element
void tarray_prepend(Tarray *a, int value);				// Insert an element at first position


void check_address(void *p);	// Test whether the memory was allocated successfully allocated
void tarray_print(Tarray* a);	// Prints public information about the array for debug purpose

// ======= tests ========
void run_all_tests();

void test_init_size();
void test_empty();
void test_push();
void test_insert();
void test_back();
void test_prepend();
void test_pop();
void test_delete();
void test_find();
void test_remove();

#endif