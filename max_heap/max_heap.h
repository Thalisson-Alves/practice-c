#include <stdbool.h>

#ifndef __MAX_HEAP_H__
#define __MAX_HEAP_H__

const int kMaxCapacity = 1000;

typedef struct max_heap
{
	// index of elements starts with 1
	int elements[1000];
	int size;
	int capacity;
} max_heap;

/* PROTOTYPE */

max_heap max_heap_new();

void max_heap_push(max_heap *heap, int value);

void max_heap_sift_up(max_heap *heap, int index);

int max_heap_top(max_heap heap);

int max_heap_size(max_heap heap);

bool max_heap_empty(max_heap heap);

int max_heap_pop(max_heap *heap);

void max_heap_sift_down(max_heap *heap, int index);

void max_heap_remove(max_heap *heap, int index);

void heapify(int *arr, int size, int index);

void build_max_heap(int arr[], int size);

void heap_sort(int *arr, int size);

void swap_elements(int *a, int *b);


/* IMPLEMENTATION */

max_heap max_heap_new()
{
	max_heap heap;
	heap.size = 0;
	heap.capacity = kMaxCapacity;
	
	return heap;
}

void max_heap_push(max_heap *heap, int value)
{
	if (heap->size == kMaxCapacity) {
		// error
		return;
	}
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

int max_heap_top(max_heap heap)
{
	return heap.size < 1? -1: heap.elements[1];
}

int max_heap_size(max_heap heap)
{
	return heap.size;
}

bool max_heap_empty(max_heap heap)
{
	return heap.size == 0;
}

int max_heap_pop(max_heap *heap)
{
	if (max_heap_empty(*heap)) {
		// error
		return 0;
	}
	int top = max_heap_top(*heap);
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
	if (index > heap->size)
		return;
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

void debug(max_heap heap)
{
	printf("Size: %i\n", heap.size);
	printf("Max element: %i\n", max_heap_top(heap));
	for (int i = 1; i <= heap.size; i++)
		printf("%i ", heap.elements[i]);
	printf("\n-----------------\n");
}

#endif