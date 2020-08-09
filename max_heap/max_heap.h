#include <stdlib.h>
#include <stdbool.h>

#ifndef __MAX_HEAP_H__
#define __MAX_HEAP_H__

/* constants for dinamic allocation */
const int kMinCapacity = 16;
const int kShirinkRate = 4;
const int kGrowthRate = 2;

typedef struct max_heap
{
	int *elements;
	int size;
	int capacity;
} max_heap;

/* PROTOTYPE */

// initialize the values, allocating memory for elements
max_heap max_heap_new();
// deallocate memory
void max_heap_destroy(max_heap *heap);
// add element to max heap
void max_heap_insert(max_heap *heap, int value);
// restore the heap propery
// propagating the given node index up up the tree
void max_heap_sift_up(max_heap *heap, int index);
// return the max value of heap, -1 if empty
int max_heap_get_max(max_heap heap);
// return size of heap
int max_heap_get_size(max_heap heap);
// return true if heap id empty
bool max_heap_get_is_empty(max_heap heap);
// return the max value of heap, -1 if empty
int max_heap_extract_max(max_heap *heap);
// restore the heap propery
// propagating the given node index down up the tree
void max_heap_sift_down(max_heap *heap, int index);
// remove element of a given index
void max_heap_remove(max_heap *heap, int index);
// same of sift_down but for 0 indexes array
void heapify(int *arr, int size, int index);
// sorts a given array to satisfy the heap propery
void build_max_heap(int arr[], int size);
// sorts a given array in non-decreasing order
void heap_sort(int *arr, int size);
// swap 2 elements
void swap_elements(int *a, int *b);
// resize the elements array to the given size
// allocating memory if needed
void max_heap_resize_for_size(max_heap *heap, int new_size);
// check address of a pointer exit the program if it's null
void check_address(void *ptr);


/* IMPLEMENTATION */

max_heap max_heap_new()
{
	max_heap heap;
	heap.size = 0;
	heap.capacity = kMinCapacity;
	heap.elements = malloc(sizeof(int) * heap.capacity);
	
	return heap;
}

void max_heap_destroy(max_heap *heap)
{
	free(heap->elements);
}

void max_heap_insert(max_heap *heap, int value)
{
	max_heap_resize_for_size(heap, heap->size + 1);
	heap->elements[++heap->size] = value;
	max_heap_sift_up(heap, heap->size);
}

void max_heap_sift_up(max_heap *heap, int index)
{
	if (!index) 
		return;
	int parent = index / 2;
	if (heap->elements[index] > heap->elements[parent]) {
		swap_elements(heap->elements + index, heap->elements + parent);
	}
	max_heap_sift_up(heap, parent);
}

int max_heap_get_max(max_heap heap)
{
	return heap.size < 1? -1: heap.elements[1];
}

int max_heap_get_size(max_heap heap)
{
	return heap.size;
}

bool max_heap_get_is_empty(max_heap heap)
{
	return heap.size == 0;
}

int max_heap_extract_max(max_heap *heap)
{
	if (max_heap_get_is_empty(*heap)) {
		return -1;
	}
	max_heap_resize_for_size(heap, heap->size - 1);
	int top = max_heap_get_max(*heap);
	heap->elements[1] = heap->elements[heap->size--];
	max_heap_sift_down(heap, 1);
	return top;
}

void max_heap_sift_down(max_heap *heap, int index)
{
	if (index > heap->size)
		return;
	int left_child = index * 2;
	int right_child = index * 2 + 1;
	int largest;
	// No childs
	if (left_child > heap->size) {
		return;
	}
	// No right child
	if (right_child > heap->size) {
		largest = left_child;
	}
	else if (heap->elements[left_child] > heap->elements[right_child]) {
		largest = left_child;
	}
	else {
		largest = right_child;
	}
	// Swap if needed
	if (heap->elements[index] < heap->elements[largest]) {
		swap_elements(&heap->elements[index], &heap->elements[largest]);
		max_heap_sift_down(heap, largest);
	}
}

void max_heap_remove(max_heap *heap, int index)
{
	if (index > heap->size || (index < 1 && heap->size)) {
		return ;
	}
	max_heap_resize_for_size(heap, heap->size - 1);
	heap->elements[index] = heap->elements[heap->size--];
	max_heap_sift_down(heap, index);
}

// Sift down for 0 index
void heapify(int *arr, int size, int index)
{
	if (index >= size)
		return;
	
	int left_child = index * 2 + 1;
	int right_child = index * 2 + 2;
	int largest;
	
	if (left_child >= size)
		return;
	
	if (right_child >= size) {
		largest = left_child;
	}
	else if (arr[left_child] > arr[right_child]) {
		largest = left_child;
	}
	else {
		largest = right_child;
	}
	
	if (arr[largest] > arr[index]) {
		swap_elements(arr + largest, arr + index);
		heapify(arr, size, largest);
	}
}

void build_max_heap(int arr[], int size)
{
	for (int i = size / 2 - 1; i >= 0; i--) {
		heapify(arr, size, i);
	}
}

void heap_sort(int arr[], int size)
{
	build_max_heap(arr, size);
	
	for (int i = size - 1; i >= 0; i--) {
		swap_elements(arr, arr + i);
		
		heapify(arr, i, 0);
	}
}

void swap_elements(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void max_heap_resize_for_size(max_heap *heap, int new_size)
{
	if (new_size > heap->size) {
		if (new_size > heap->capacity) {
			// grow tree
			int new_capacity = heap->capacity * kGrowthRate;
			int *new_elements = realloc(heap->elements, sizeof(int) * new_capacity);
			check_address(new_elements);
			heap->elements = new_elements;
			heap->capacity = new_capacity;
		}
	}
	else {
		if (heap->capacity / kShirinkRate > new_size) {
			int new_capacity = heap->capacity / kShirinkRate;
			if (new_capacity < kMinCapacity) {
				new_capacity = kMinCapacity;
			}
			// Do nothing
			if (new_capacity == heap->capacity) {
				return ;
			}
			int *new_elements = realloc(heap->elements, sizeof(int) * new_capacity);
			check_address(new_elements);
			heap->elements = new_elements;
			heap->capacity = new_capacity;
		}
	}
}

void check_address(void *ptr)
{
	if (!ptr) {
		printf("Bad allocation\n");
		exit(EXIT_FAILURE);
	}
}

void debug(max_heap heap)
{
	printf("Size: %i\n", heap.size);
	printf("Capacity: %i\n", heap.capacity);
	printf("Max element: %i\n", max_heap_get_max(heap));
	for (int i = 1; i <= heap.size; i++)
		printf("%i ", heap.elements[i]);
	printf("\n-----------------\n");
}

#endif