#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "array.c"

void run_example();

int main()
{
	run_all_tests();
	run_example();
	
	return EXIT_SUCCESS;
}


void run_example(){
	printf("Creating an array with an especific size.\n");
	printf("How much elements would you like to store? ");
	int size;
	scanf("%d", &size);
	Tarray *arr = tarray_new_size(size);
	tarray_print(arr);
	tarray_destroy(arr);
	printf("Creating an array that you don't know the size previously.\n");
	Tarray *a = tarray_new();
	tarray_print(a);
	printf("Pushing 12 values to it.\n");
	for(int i=0; i<12; i++)
		tarray_push(a, i);
	tarray_print(a);
	printf("Accessing the index 5: %d.\n", tarray_at(a, 5));
	printf("Adding 5 more values to it.\n");
	for(int i=1; i<=5; i++)
		tarray_push(a, i*i*5);
	tarray_print(a);
	printf("Inserting value 111 at index 5:\n");
	tarray_insert(a, 5, 111);
	tarray_print(a);
	printf("Prepending value 12.\n");
	tarray_prepend(a, 12);
	tarray_print(a);
	printf("Poping the last element wich value is %d.\n", tarray_pop(a));
	tarray_print(a);
	printf("Deleting element at index 3.\n");
	tarray_delete(a, 3);
	tarray_print(a);
	printf("The last digit of the array is: %d\n", tarray_back(a));
	printf("Removing element 5.\n");
	tarray_remove(a, 5);
	tarray_print(a);
	printf("Popping elements until the size reach 7.\n");
	while(tarray_size(a) > 7){
		tarray_pop(a);
	}
	tarray_print(a);
	tarray_destroy(a);
}