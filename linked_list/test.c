void run_all_tests(){
	test_size();
	test_push_front();
	test_empty();
	test_front();
	test_back();
	test_pop_front();
	test_push_back();
	test_pop_back();
	test_insert();
	test_value_at();
	test_erase();
	test_value_n_from_end();
	test_reverse();
	test_remove();
}

void test_size() {
	Tlinked_list *tester = tlinked_list_new();
	assert(tlinked_list_size(tester) == 0);
	
	tlinked_list_push_back(tester, 4);
	assert(tlinked_list_size(tester) == 1);
	
	tlinked_list_destroy(tester);
}

void test_push_front() {
	Tlinked_list *tester = tlinked_list_new();
	assert(tlinked_list_size(tester) == 0);
	
	tlinked_list_push_front(tester, 10);
	assert(tlinked_list_size(tester) == 1);
	
	tlinked_list_push_front(tester, 44);
	assert(tlinked_list_size(tester) == 2);
	
	tlinked_list_push_front(tester, 33);
	assert(tlinked_list_size(tester) == 3);
	
	tlinked_list_destroy(tester);
}

void test_empty() {
	Tlinked_list *tester = tlinked_list_new();
	assert(tlinked_list_empty(tester));
	
	tlinked_list_push_front(tester, 20);
	assert(!tlinked_list_empty(tester));
	
	tlinked_list_pop_front(tester);
	assert(tlinked_list_empty(tester));
	
	tlinked_list_destroy(tester);
}

void test_front() {
	Tlinked_list *tester = tlinked_list_new();
	tlinked_list_push_back(tester, 49);
	assert(tlinked_list_front(tester) == 49);
	
	tlinked_list_push_front(tester, 81);
	assert(tlinked_list_front(tester) == 81);

	tlinked_list_push_back(tester, 2);
	assert(tlinked_list_front(tester) == 81);
	
	tlinked_list_destroy(tester);
}

void test_back() {
	Tlinked_list *tester = tlinked_list_new();
	
	tlinked_list_push_front(tester, 5);
	assert(tlinked_list_back(tester) == 5);
	
	tlinked_list_push_back(tester, 30);
	assert(tlinked_list_back(tester) == 30);
	
	tlinked_list_push_front(tester, 7);
	assert(tlinked_list_back(tester) == 30);
	
	tlinked_list_destroy(tester);
}

void test_pop_front() {
	Tlinked_list *tester = tlinked_list_new();
	
	tlinked_list_push_front(tester, 11);
	assert(tlinked_list_front(tester) == 11);
	
	tlinked_list_push_front(tester, 22);
	assert(tlinked_list_front(tester) == 22);
	
	tlinked_list_pop_front(tester);
	assert(tlinked_list_front(tester) == 11);
	
	tlinked_list_pop_front(tester);
	assert(tlinked_list_empty(tester));
	
	tlinked_list_destroy(tester);
}

void test_push_back() {
	Tlinked_list *tester = tlinked_list_new();
	tlinked_list_push_front(tester, 8);
	tlinked_list_push_front(tester, 33);
	assert(tlinked_list_back(tester) == 8);
	
	tlinked_list_push_back(tester, 45);
	assert(tlinked_list_back(tester) == 45);
	
	tlinked_list_destroy(tester);
}

void test_pop_back() {
	Tlinked_list *tester = tlinked_list_new();
	
	tlinked_list_push_back(tester, 10);
	tlinked_list_push_back(tester, 12);
	tlinked_list_push_back(tester, 16);
	tlinked_list_push_back(tester, 19);
	assert(tlinked_list_back(tester) == 19);
	assert(tlinked_list_size(tester) == 4);
	
	tlinked_list_pop_back(tester);
	assert(tlinked_list_back(tester) == 16);
	assert(tlinked_list_size(tester) == 3);
	
	tlinked_list_pop_back(tester);
	assert(tlinked_list_back(tester) == 12);
	assert(tlinked_list_size(tester) == 2);
	
	tlinked_list_pop_back(tester);
	tlinked_list_pop_back(tester);
	
	assert(tlinked_list_empty(tester));
	
	tlinked_list_destroy(tester);
}

void test_value_at() {
	Tlinked_list *tester = tlinked_list_new();
	
	tlinked_list_push_back(tester, 9);
	tlinked_list_push_back(tester, 99);
	tlinked_list_push_back(tester, 999);
	
	assert(tlinked_list_value_at(tester, 0) == 9);
	assert(tlinked_list_value_at(tester, 1) == 99);
	assert(tlinked_list_value_at(tester, 2) == 999);
	
	tlinked_list_destroy(tester);
}

void test_insert() {
	Tlinked_list *tester = tlinked_list_new();
	
	tlinked_list_push_front(tester, 13);
	tlinked_list_insert(tester, 0, 10);
	assert(tlinked_list_size(tester) == 2);
	assert(tlinked_list_value_at(tester, 0) == 10);
	
	tlinked_list_insert(tester, 1, 11);
	assert(tlinked_list_value_at(tester, 1) == 11);
	assert(tlinked_list_size(tester) == 3);
	
	tlinked_list_insert(tester, 2, 12);
	assert(tlinked_list_value_at(tester, 0) == 10);
	assert(tlinked_list_value_at(tester, 1) == 11);
	assert(tlinked_list_value_at(tester, 2) == 12);
	
	tlinked_list_destroy(tester);
}

void test_erase() {
	Tlinked_list *tester = tlinked_list_new();
	
	tlinked_list_push_front(tester, 13);
	tlinked_list_insert(tester, 0, 10);
	
	tlinked_list_erase(tester, 0);
	
	assert(tlinked_list_value_at(tester, 0) == 13);
	
	tlinked_list_push_front(tester, 77);
	tlinked_list_push_back(tester, 777);
	
	tlinked_list_erase(tester, 0);
	assert(tlinked_list_value_at(tester, 0) == 13);
	assert(tlinked_list_value_at(tester, 1) == 777);
	assert(tlinked_list_size(tester) == 2);
	
	tlinked_list_push_back(tester, 88);
	tlinked_list_erase(tester, 0);
	assert(tlinked_list_value_at(tester, 1) == 88);
	
	tlinked_list_erase(tester, 1);
	assert(tlinked_list_value_at(tester, 0) == 777);
	assert(tlinked_list_size(tester) == 1);

	tlinked_list_erase(tester, 0);
	assert(tlinked_list_empty(tester));
	
	tlinked_list_destroy(tester);
}

void test_value_n_from_end() {
	Tlinked_list *tester = tlinked_list_new();
	
	tlinked_list_push_back(tester, 46);
	assert(tlinked_list_value_n_from_end(tester, 1) == 46);
	
	tlinked_list_push_back(tester, 13);
	assert(tlinked_list_value_n_from_end(tester, 1) == 13);

	tlinked_list_push_back(tester, 79);
	tlinked_list_push_back(tester, 97);
	tlinked_list_push_back(tester, 64);
	tlinked_list_push_back(tester, 31);
	
	assert(tlinked_list_value_n_from_end(tester, 1) == 31);
	assert(tlinked_list_value_n_from_end(tester, 3) == 97);
	assert(tlinked_list_value_n_from_end(tester, 5) == 13);
	assert(tlinked_list_value_n_from_end(tester, 2) == 64);
	assert(tlinked_list_value_n_from_end(tester, 4) == 79);
	
	tlinked_list_destroy(tester);
}

void test_reverse() {
	Tlinked_list *tester = tlinked_list_new();
	
	tlinked_list_reverse(tester);
	
	tlinked_list_push_back(tester, 1);
	tlinked_list_reverse(tester);
	assert(tlinked_list_size(tester) == 1);
	assert(tlinked_list_value_at(tester, 0) == 1);
	
	tlinked_list_push_back(tester, 2);
	tlinked_list_push_back(tester, 3);
	tlinked_list_push_back(tester, 4);
	tlinked_list_push_back(tester, 5);
	tlinked_list_push_back(tester, 6);
	
	tlinked_list_reverse(tester);
	
	assert(tlinked_list_value_at(tester, 0) == 6);
	assert(tlinked_list_value_at(tester, 1) == 5);
	assert(tlinked_list_value_at(tester, 2) == 4);
	assert(tlinked_list_value_at(tester, 3) == 3);
	assert(tlinked_list_value_at(tester, 4) == 2);
	assert(tlinked_list_value_at(tester, 5) == 1);
	
	tlinked_list_destroy(tester);
}

void test_remove() {
	Tlinked_list *tester = tlinked_list_new();
	
	tlinked_list_push_back(tester, 8);
	tlinked_list_push_back(tester, 44);
	tlinked_list_push_back(tester, 66);
	tlinked_list_push_back(tester, 44);
	
	tlinked_list_remove_value(tester, 44);
	assert(tlinked_list_size(tester) == 3);
	assert(tlinked_list_value_at(tester, 1) == 66);
	assert(tlinked_list_value_at(tester, 2) == 44);
	
	tlinked_list_remove_value(tester, 8);
	assert(tlinked_list_size(tester) == 2);
	assert(tlinked_list_value_at(tester, 0) == 66);
	
	tlinked_list_remove_value(tester, 66);
	tlinked_list_remove_value(tester, 44);
	assert(tlinked_list_size(tester) == 0);
	
	tlinked_list_destroy(tester);
}