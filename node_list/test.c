void run_all_tests(){
	test_size();
	test_push_front();
	test_empty();
	test_front();
	test_back();
	test_pop_front();
	test_push_back();
	test_pop_back();
	test_value_at();
	test_insert();
	test_erase();
	test_value_n_from_end();
	test_reverse();
	test_remove();
}

void test_size() {
	Tnode_list *head = NULL;
	assert(tnode_list_size(head) == 0);
	
	tnode_list_push_back(&head, 4);
	assert(tnode_list_size(head) == 1);
	
	tnode_list_destroy(head);
}

void test_push_front() {
	Tnode_list *head = NULL;
	assert(tnode_list_size(head) == 0);
	
	tnode_list_push_front(&head, 10);
	assert(tnode_list_size(head) == 1);
	
	tnode_list_push_front(&head, 44);
	assert(tnode_list_size(head) == 2);
	
	tnode_list_push_front(&head, 33);
	assert(tnode_list_size(head) == 3);
	
	tnode_list_destroy(head);
}

void test_empty() {
	Tnode_list *head = NULL;
	assert(tnode_list_empty(head));
	
	tnode_list_push_front(&head, 20);
	assert(!tnode_list_empty(head));
	
	tnode_list_pop_front(&head);
	assert(tnode_list_empty(head));
	
	tnode_list_destroy(head);
}

void test_front() {
	Tnode_list *head = NULL;
	tnode_list_push_back(&head, 49);
	assert(tnode_list_front(head) == 49);
	
	tnode_list_push_front(&head, 81);
	assert(tnode_list_front(head) == 81);

	tnode_list_push_back(&head, 2);
	assert(tnode_list_front(head) == 81);
	
	tnode_list_destroy(head);
}

void test_back() {
	Tnode_list *head = NULL;
	
	tnode_list_push_front(&head, 5);
	assert(tnode_list_back(head) == 5);
	
	tnode_list_push_back(&head, 30);
	assert(tnode_list_back(head) == 30);
	
	tnode_list_push_front(&head, 7);
	assert(tnode_list_back(head) == 30);
	
	tnode_list_destroy(head);
}

void test_pop_front() {
	Tnode_list *head = NULL;
	
	tnode_list_push_front(&head, 11);
	assert(tnode_list_front(head) == 11);
	
	tnode_list_push_front(&head, 22);
	assert(tnode_list_front(head) == 22);
	
	tnode_list_pop_front(&head);
	assert(tnode_list_front(head) == 11);
	
	tnode_list_pop_front(&head);
	assert(tnode_list_empty(head));
	
	tnode_list_destroy(head);
}

void test_push_back() {
	Tnode_list *head = NULL;
	tnode_list_push_front(&head, 8);
	tnode_list_push_front(&head, 33);
	assert(tnode_list_back(head) == 8);
	
	tnode_list_push_back(&head, 45);
	assert(tnode_list_back(head) == 45);
	
	tnode_list_destroy(head);
}

void test_pop_back() {
	Tnode_list *head = NULL;
	
	tnode_list_push_back(&head, 10);
	tnode_list_push_back(&head, 12);
	tnode_list_push_back(&head, 16);
	tnode_list_push_back(&head, 19);
	assert(tnode_list_back(head) == 19);
	assert(tnode_list_size(head) == 4);
	
	tnode_list_pop_back(&head);
	assert(tnode_list_back(head) == 16);
	assert(tnode_list_size(head) == 3);
	
	tnode_list_pop_back(&head);
	assert(tnode_list_back(head) == 12);
	assert(tnode_list_size(head) == 2);
	
	tnode_list_pop_back(&head);
	tnode_list_pop_back(&head);
	
	assert(tnode_list_empty(head));
	
	tnode_list_destroy(head);
}

void test_value_at() {
	Tnode_list *head = NULL;
	
	tnode_list_push_back(&head, 9);
	tnode_list_push_back(&head, 99);
	tnode_list_push_back(&head, 999);
	
	assert(tnode_list_value_at(head, 0) == 9);
	assert(tnode_list_value_at(head, 1) == 99);
	assert(tnode_list_value_at(head, 2) == 999);
	
	tnode_list_destroy(head);
}

void test_insert() {
	Tnode_list *head = NULL;
	
	tnode_list_push_front(&head, 13);
	tnode_list_insert(&head, 0, 10);
	assert(tnode_list_size(head) == 2);
	assert(tnode_list_value_at(head, 0) == 10);
	
	tnode_list_insert(&head, 1, 11);
	assert(tnode_list_value_at(head, 1) == 11);
	assert(tnode_list_size(head) == 3);
	
	tnode_list_insert(&head, 2, 12);
	assert(tnode_list_value_at(head, 0) == 10);
	assert(tnode_list_value_at(head, 1) == 11);
	assert(tnode_list_value_at(head, 2) == 12);
	
	tnode_list_destroy(head);
}

void test_erase() {
	Tnode_list *head = NULL;
	
	tnode_list_push_front(&head, 13);
	tnode_list_insert(&head, 0, 10);
	
	tnode_list_erase(&head, 0);
	
	assert(tnode_list_value_at(head, 0) == 13);
	
	tnode_list_push_front(&head, 77);
	tnode_list_push_back(&head, 777);
	
	tnode_list_erase(&head, 0);
	assert(tnode_list_value_at(head, 0) == 13);
	assert(tnode_list_value_at(head, 1) == 777);
	assert(tnode_list_size(head) == 2);
	
	tnode_list_push_back(&head, 88);
	tnode_list_erase(&head, 0);
	assert(tnode_list_value_at(head, 1) == 88);
	
	tnode_list_erase(&head, 1);
	assert(tnode_list_value_at(head, 0) == 777);
	assert(tnode_list_size(head) == 1);

	tnode_list_erase(&head, 0);
	assert(tnode_list_empty(head));
	
	tnode_list_destroy(head);
}

void test_value_n_from_end() {
	Tnode_list *head = NULL;
	
	tnode_list_push_back(&head, 46);
	assert(tnode_list_value_n_from_end(head, 1) == 46);
	
	tnode_list_push_back(&head, 13);
	assert(tnode_list_value_n_from_end(head, 1) == 13);

	tnode_list_push_back(&head, 79);
	tnode_list_push_back(&head, 97);
	tnode_list_push_back(&head, 64);
	tnode_list_push_back(&head, 31);
	
	assert(tnode_list_value_n_from_end(head, 1) == 31);
	assert(tnode_list_value_n_from_end(head, 3) == 97);
	assert(tnode_list_value_n_from_end(head, 5) == 13);
	assert(tnode_list_value_n_from_end(head, 2) == 64);
	assert(tnode_list_value_n_from_end(head, 4) == 79);
	
	tnode_list_destroy(head);
}

void test_reverse() {
	Tnode_list *head = NULL;
	
	tnode_list_reverse(&head);
	
	tnode_list_push_back(&head, 1);
	tnode_list_reverse(&head);
	assert(tnode_list_size(head) == 1);
	assert(tnode_list_value_at(head, 0) == 1);
	
	tnode_list_push_back(&head, 2);
	tnode_list_push_back(&head, 3);
	tnode_list_push_back(&head, 4);
	tnode_list_push_back(&head, 5);
	tnode_list_push_back(&head, 6);
	
	tnode_list_reverse(&head);
	
	assert(tnode_list_value_at(head, 0) == 6);
	assert(tnode_list_value_at(head, 1) == 5);
	assert(tnode_list_value_at(head, 2) == 4);
	assert(tnode_list_value_at(head, 3) == 3);
	assert(tnode_list_value_at(head, 4) == 2);
	assert(tnode_list_value_at(head, 5) == 1);
	
	tnode_list_destroy(head);
}

void test_remove() {
	Tnode_list *head = NULL;
	
	tnode_list_push_back(&head, 8);
	tnode_list_push_back(&head, 44);
	tnode_list_push_back(&head, 66);
	tnode_list_push_back(&head, 44);
	
	tnode_list_remove_value(&head, 44);
	assert(tnode_list_size(head) == 3);
	assert(tnode_list_value_at(head, 1) == 66);
	assert(tnode_list_value_at(head, 2) == 44);
	
	tnode_list_remove_value(&head, 8);
	assert(tnode_list_size(head) == 2);
	assert(tnode_list_value_at(head, 0) == 66);
	
	tnode_list_remove_value(&head, 66);
	tnode_list_remove_value(&head, 44);
	assert(tnode_list_size(head) == 0);
	
	tnode_list_destroy(head);
}