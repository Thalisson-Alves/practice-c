Tarray *tarray_new(){
	Tarray *a = (Tarray*)malloc(sizeof(Tarray));
	check_address(a);
	a->capacity = MIN_CAPACITY;
	a->size = 0;
	a->data = (int*)malloc(a->capacity*sizeof(int));
	check_address(a->data);
	return a;
}

Tarray *tarray_new_size(int size){
	int capacity = tarray_determine_capacity(size);
	Tarray *a = (Tarray*)malloc(capacity*sizeof(Tarray));
	check_address(a);
	a->capacity = capacity;
	a->size = size;
	a->data = (int*)malloc(a->capacity*sizeof(int));
	check_address(a->data);
	for(int i=0; i<a->size; i++)
		a->data[i] = 0;
	return a;
}

void tarray_destroy(Tarray* a){
	free(a->data);
	free(a);
}


int tarray_back(Tarray* a){
	if(tarray_empty(a)){
		printf("Index out of bound!\n");
		exit(EXIT_FAILURE);
	}
	return tarray_at(a, tarray_size(a)-1);
}

int tarray_front(Tarray *a){
	if(tarray_empty(a)){
		printf("Index out of bound!\n");
		exit(EXIT_FAILURE);
	}
	return *a->data;
}

int tarray_at(Tarray* a, int index){
	if(a->size <= index || index < 0){
		printf("Index out of bound!\n");
		exit(EXIT_FAILURE);
	}
	return *(a->data + index);
}

int tarray_find(Tarray *a, int value){
	int index = -1;
	for(int i=0; i<a->size; i++)
		if(a->data[i] == value){
			index = i;
			break;
		}
	return index;
}


int tarray_size(Tarray* a){ return a->size; }

void tarray_resize_for_size(Tarray *a, int new_size){
	if(new_size == a->capacity || new_size < a->capacity / SHRINK_RATE){
		int new_capacity = tarray_determine_capacity(new_size);
		int *new_data = (int*)realloc(a->data, new_capacity*sizeof(int));
		check_address(new_data);
		a->data = new_data;
		a->capacity = new_capacity;
	}
}

int tarray_determine_capacity(int size){
	int actual_capacity = MIN_CAPACITY;
	while(actual_capacity/GROWTH_RATE < size)
		actual_capacity *= GROWTH_RATE;
	
	return actual_capacity;
}

int tarray_capacity(Tarray* a){ return a->capacity; }

bool tarray_empty(Tarray* a){ return a->size == 0; }


int tarray_pop(Tarray* a){
	tarray_resize_for_size(a, --a->size);
	return a->data[a->size];
}

void tarray_delete(Tarray *a, int index){
	if(0 > index || index >= a->size--){
		printf("Index out of bound!\n");
		exit(EXIT_FAILURE);
	}
	tarray_resize_for_size(a, a->size);
	for(int i=index; i<=a->size; i++)
		a->data[i] = a->data[i+1];
}

void tarray_remove(Tarray *a, int value){
	int new_size = 0;
	int old_size = a->size;
	for(int i=0; i<old_size; i++)
		if(a->data[i] != value)
			a->data[new_size++] = a->data[i];
	a->size = new_size;
	tarray_resize_for_size(a, a->size);
}

void tarray_push(Tarray* a, int n){
	tarray_resize_for_size(a, a->size+1);
	a->data[a->size++] = n;
}

void tarray_insert(Tarray* a, int index, int value){
	if(a->size <= index || index < 0){
		printf("Index out of bound!\n");
		exit(EXIT_FAILURE);
	}
	tarray_push(a, value);
	for(int i=a->size-1; i>index; i--){
		int temp = a->data[i];
		a->data[i] = a->data[i-1];
		a->data[i-1] = temp;
	}
}

void tarray_prepend(Tarray* a, int value){
	if(a->size > 0)
		tarray_insert(a, 0, value);
	else
		tarray_push(a, value);
}


void tarray_print(Tarray* a){
	printf("Size: %d\n", a->size);
	printf("Capacity: %d\n", a->capacity);
	printf("Elements:\n");
	for(int i=0; i<a->size; i++)
		printf("TArray[%d] = %d\n", i, a->data[i]);
	printf("\n===----------------===\n");
}

void check_address(void *p){
	if(!p){
		printf("Memory allocantion faild!\n");
		exit(EXIT_FAILURE);
	}
}


void run_all_tests(){
	test_init_size();
	test_empty();
	test_push();
	test_insert();
	test_back();
	test_prepend();
	test_pop();
	test_delete();
	test_find();
	test_remove();
}

void test_init_size(){
	Tarray* aptr = tarray_new();
	int initial_size = tarray_size(aptr);
	assert(initial_size == 0);
	tarray_destroy(aptr);
}

void test_empty(){
	Tarray* aptr = tarray_new();
	assert(tarray_empty(aptr));
	tarray_destroy(aptr);
}

void test_push(){
	Tarray* aptr = tarray_new();
	int init_capacity = tarray_capacity(aptr);
	for(int i=0; i<init_capacity+2; i++)
		tarray_push(aptr, i);
	assert(2*init_capacity == tarray_capacity(aptr));
	tarray_destroy(aptr);
}

void test_insert(){
	Tarray* aptr = tarray_new_size(10);
	int index = 2;
	int value = 111;
	int initial_size = aptr->size;
	tarray_insert(aptr, index, value);
	assert(aptr->data[index] == value && initial_size+1 == aptr->size);
	tarray_destroy(aptr);
}

void test_back(){
	Tarray* a = tarray_new_size(3);
	a->data[2] = 10;
	assert(tarray_back(a) == 10);
	tarray_destroy(a);
}

void test_prepend(){
	Tarray* a = tarray_new();
	tarray_push(a, 7);
	tarray_prepend(a, 99);
	assert(tarray_at(a, 0) == 99);
	tarray_destroy(a);
}

void test_pop(){
	Tarray *a = tarray_new_size(12);
	int init_capacity = tarray_capacity(a);
	for(int i=0; i<a->size; i++)
		a->data[i] = i;
	while(tarray_size(a) >= init_capacity / SHRINK_RATE){
		assert(tarray_pop(a) == tarray_size(a));
	}
	assert(tarray_capacity(a) * 2 == init_capacity);
	tarray_destroy(a);
}

void test_delete(){
	Tarray* a = tarray_new();
	tarray_push(a, 12);
	tarray_push(a, 20);
	tarray_push(a, 4);
	tarray_push(a, 1);
	tarray_push(a, 9);
	tarray_push(a, 0);
	tarray_delete(a, 2);
	assert(tarray_at(a, 2) == 1 && tarray_size(a) == 5);
	tarray_destroy(a);
}

void test_find(){
	Tarray* a = tarray_new();
	tarray_push(a, 12);
	tarray_push(a, 20);
	tarray_push(a, 4);
	tarray_push(a, 1);
	tarray_push(a, 9);
	tarray_push(a, 0);
	assert(tarray_find(a, 3) == -1 && tarray_find(a, 9) == 4);
	tarray_destroy(a);
}

void test_remove(){
	Tarray* a = tarray_new();
	tarray_push(a, 12);
	tarray_push(a, 20);
	tarray_push(a, 3);
	tarray_push(a, 1);
	tarray_push(a, 9);
	tarray_push(a, 3);
	tarray_push(a, 3);
	tarray_remove(a, 3);
	assert(a->size == 4);
	for(int i=0; i<a->size; i++)
		assert(a->data[i] != 3);
	tarray_destroy(a);
}