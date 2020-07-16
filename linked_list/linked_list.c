Tlinked_list *tlinked_list_new(){
	Tlinked_list *tlist = malloc(sizeof(Tlinked_list));
	check_address(tlist);
	tlist->head = NULL;
	tlist->tail = NULL;
	return tlist;
}

void tlinked_list_destroy(Tlinked_list *tlist){
	struct Single_node *current = tlist->head;
	while(current){
		struct Single_node *next = current->next;
		free(current);
		current = next;
	}
	free(tlist);
}

int tlinked_list_front(Tlinked_list *tlist){
	if(tlinked_list_empty(tlist)){
		printf("Can not access front from an empty list.\n");
		exit(EXIT_FAILURE);
	}
	return tlist->head->data;
}

int tlinked_list_back(Tlinked_list *tlist){
	if(tlinked_list_empty(tlist)){
		printf("Can not access back from an empty list.\n");
		exit(EXIT_FAILURE);
	}
	return tlist->tail->data;
}

int tlinked_list_value_n_from_end(Tlinked_list *tlist, int n){
	struct Single_node *target = tlist->head;
	struct Single_node *current = tlist->head;
	
	for(int i=0; i<n; i++){
		if(current)
			current = current->next;
		else{
			printf("List not long enough.\n");
			exit(EXIT_FAILURE);
		}
	}
	while(current){
		current = current->next;
		target = target->next;
	}
	
	return target->data;
}

int tlinked_list_value_at(Tlinked_list *tlist, int index){
	if(tlinked_list_empty(tlist)){
		printf("Index out of bound.\n");
		exit(EXIT_FAILURE);
	}
	struct Single_node *current = tlist->head;
	for(int i=0; i<index; i++){
		if(current)
			current = current->next;
		else{
			printf("Index out of bound.\n");
			exit(EXIT_FAILURE);
		}
	}
	return current->data;
}

int tlinked_list_size(Tlinked_list *tlist){
	int size = 0;
	struct Single_node *current = tlist->head;
	while(current){
		size++;
		current = current->next;
	}
	return size;
}

bool tlinked_list_empty(Tlinked_list *tlist){
	return !tlist->head && !tlist->tail;
}

void tlinked_list_push_front(Tlinked_list *tlist, int value){
	struct Single_node *node = malloc(sizeof(struct Single_node));
	check_address(node);
	node->data = value;
	node->next = tlist->head;
	tlist->head = node;
	if(tlist->tail == NULL)
		tlist->tail = node;
}

void tlinked_list_pop_front(Tlinked_list *tlist){
	if(tlinked_list_empty(tlist)){
		printf("List already empty.\n");
		exit(EXIT_FAILURE);
	}
	struct Single_node *temp = tlist->head;
	tlist->head = tlist->head->next;
	if(temp == tlist->tail)
		tlist->tail = tlist->head;
	free(temp);
}

void tlinked_list_push_back(Tlinked_list *tlist, int value){
	struct Single_node *node = malloc(sizeof(struct Single_node));
	node->data = value;
	node->next = NULL;
	if(tlinked_list_empty(tlist))
		tlist->head = node;
	else
		tlist->tail->next = node;
	tlist->tail = node;
}

void tlinked_list_pop_back(Tlinked_list *tlist){
	if(tlinked_list_empty(tlist)){
		printf("List already empty.\n");
		exit(EXIT_FAILURE);
	}
	struct Single_node *last = tlist->head;
	if(last == tlist->tail){
		free(tlist->tail);
		tlist->tail = NULL;
		tlist->head = NULL;
		return;
	}
	while(last->next != tlist->tail)
		last = last->next;
	free(tlist->tail);
	last->next = NULL;
	tlist->tail = last;
}

void tlinked_list_insert(Tlinked_list *tlist, int index, int value){
	if(tlinked_list_empty(tlist)){
		printf("Index out of bound.\n");
		exit(EXIT_FAILURE);
	}
	if(index == 0){
		tlinked_list_push_front(tlist, value);
		return;
	}
	int at = 0;
	struct Single_node *current = tlist->head;
	while(at < index-1 && current){
		at++;
		current = current->next;
	}
	struct Single_node *next = current->next;
	if(at != index-1 || !next){
		printf("Index out of bound.\n");
		exit(EXIT_FAILURE);
	}
	struct Single_node *node = malloc(sizeof(struct Single_node));
	node->data = value;
	node->next = next;
	current->next = node;
}

void tlinked_list_erase(Tlinked_list *tlist, int index){
	if(tlinked_list_empty(tlist)){
		printf("Index out of bound.\n");
		exit(EXIT_FAILURE);
	}
	if(index == 0){
		tlinked_list_pop_front(tlist);
		return;
	}
	int at = 0;
	struct Single_node *node = tlist->head;
	while(node && at<index-1){
		at++;
		node = node->next;
	}
	struct Single_node *temp = node->next;
	if(at+1 != index || !temp){
		printf("Index out of bound.\n");
		exit(EXIT_FAILURE);
	}
	node->next = node->next->next;
	if(tlist->tail == temp)
		tlist->tail = node;
	free(temp);
}

void tlinked_list_reverse(Tlinked_list *tlist){
	struct Single_node *prev = NULL;
	struct Single_node *current = tlist->head;
	while(current){
		struct Single_node *next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	tlist->head = prev;
}

void tlinked_list_remove_value(Tlinked_list *tlist, int value){
	struct Single_node *current = tlist->head;
	if(current && current->data == value){
		tlinked_list_pop_front(tlist);
		return;
	}
	struct Single_node *temp = current->next;
	while(temp){
		if(temp->data == value){
			if(temp == tlist->tail)
				tlist->tail = current;
			current->next = temp->next;
			free(temp);
			break;
		}
		current = current->next;
		temp = temp->next;
	}
}

void check_address(void *ptr){
	if(ptr == NULL){
		printf("Bad allocation.\n");
		exit(EXIT_FAILURE);
	}
}

void tlinked_list_debug(Tlinked_list *tlist){
	printf("Size = %d\n", tlinked_list_size(tlist));
	printf("Head = %p\n", (void *)tlist->head);
	printf("Tail = %p\n", (void *)tlist->tail);
	printf("Elements:\n");
	struct Single_node *current = tlist->head;
	int i=0;
	while(current){
		printf("tlist[%d] = %d\n", i++, current->data);
		current = current->next;
	}
	printf("-------------------\n");
}