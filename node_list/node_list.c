void tnode_list_destroy(Tnode_list *head){
	while(head){
		Tnode_list *next = head->next;
		free(head);
		head = next;
	}
}

int tnode_list_front(Tnode_list *head){
	if(head)
		return head->data;
	printf("Cannot access front from an empty list.\n");
	exit(EXIT_FAILURE);
}

int tnode_list_back(Tnode_list *head){
	if(!head){
		printf("Cannot access back from an empty list.\n");
		exit(EXIT_FAILURE);
	}
	Tnode_list *current = head;
	while(current->next)
		current = current->next;
	return current->data;
}


int tnode_list_value_n_from_end(Tnode_list *head, int n){
	if(n <= 0){
		printf("n must be greater than 0.\n");
		exit(EXIT_FAILURE);
	}
	Tnode_list *current = head;
	Tnode_list *target = head;
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

int tnode_list_value_at(Tnode_list *head, int index){
	if(index < 0){
		printf("Index out of bound.\n");
		exit(EXIT_FAILURE);
	}
	Tnode_list *current = head;
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

int tnode_list_size(Tnode_list *head){
	int size;
	Tnode_list *node = head;
	for(size=0; node; size++, node = node->next){}
	return size;
}

bool tnode_list_empty(Tnode_list *head){ return !head; }

void tnode_list_push_front(Tnode_list **head, int value){
	Tnode_list *node = (Tnode_list *)malloc(sizeof(Tnode_list));
	check_address(node);
	node->data = value;
	node->next = *head;
	*head = node;
}

void tnode_list_pop_front(Tnode_list **head){
	if(tnode_list_empty(*head)){
		printf("List already empty.\n");
		exit(EXIT_FAILURE);
	}
	Tnode_list *temp = *head;
	*head = (*head)->next;
	free(temp);
}

void tnode_list_push_back(Tnode_list **head, int value){
	Tnode_list *current = *head;
	if(!current){
		tnode_list_push_front(head, value);
		return;
	}
	Tnode_list *last = malloc(sizeof(Tnode_list));
	last->data = value;
	last->next = NULL;
	while(current->next){
		current = current->next;
	}
	current->next = last;
}

void tnode_list_pop_back(Tnode_list **head){
	Tnode_list *temp = *head;
	if(!temp){
		printf("List already empty.\n");
		exit(EXIT_FAILURE);
	}
	if(!temp->next){
		*head = NULL;
		free(temp);
		return ;
	}
	Tnode_list *last = temp;
	while(temp->next){
		last = temp;
		temp = temp->next;
	}
	free(temp);
	last->next = NULL;
}

void tnode_list_insert(Tnode_list **head, int index, int value){
	if(index < 0 || tnode_list_empty(*head)){
		printf("Index out of bound.\n");
		exit(EXIT_FAILURE);
	}
	if(!index){
		tnode_list_push_front(head, value);
		return;
	}
	Tnode_list *temp = *head;
	for(int i=0; i<index-1; i++){
		if(temp)
			temp = temp->next;
		else{
			printf("Index out of bound.\n");
			exit(EXIT_FAILURE);
		}
	}
	Tnode_list *next = temp->next;
	Tnode_list *node = malloc(sizeof(Tnode_list));
	check_address(node);
	temp->next = node;
	node->data = value;
	node->next = next;
}

void tnode_list_erase(Tnode_list **head, int index){
	if(index < 0 || tnode_list_empty(*head)){
		printf("Index out of bound.\n");
		exit(EXIT_FAILURE);
	}
	if(!index){
		tnode_list_pop_front(head);
		return ;
	}
	Tnode_list *current = *head;
	for(int i=0; i<index-1; i++){
		if(current)
			current = current->next;
		else{
			printf("Index out bound.\n");
			exit(EXIT_FAILURE);
		}
	}
	Tnode_list *temp = current->next;
	current->next = (temp? temp->next: NULL);
	free(temp);
}

void tnode_list_reverse(Tnode_list **head){
	Tnode_list *prev = NULL;
	Tnode_list *current = *head;
	while(current){
		Tnode_list *next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}

void tnode_list_remove_value(Tnode_list **head, int value){
	Tnode_list *current = *head;
	Tnode_list *prev = NULL;
	if(current && current->data == value){
		tnode_list_pop_front(head);
		return;
	}
	while(current){
		if(current->data == value){
			prev->next = current->next;
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void check_address(void *ptr){
	if(!ptr){
		printf("Bad allocation.\n");
		exit(EXIT_FAILURE);
	}
}

void tnode_list_debug(Tnode_list *head){
	Tnode_list *node = head;
	printf("Head = %p.\n", (void *)node);
	for(int i=0; node; i++, node = node->next){
		printf("Node[%d] = %d\n", i, node->data);
	}
	printf("-------------------\n");
}