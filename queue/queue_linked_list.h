#include <stdbool.h>

#ifndef __QUEUE_LINKED_LIST_H__
#define __QUEUE_LINKED_LIST_H__

struct SingleNode{
	int data;
	struct SingleNode *next;
};

typedef struct QueueImplementation{
	struct SingleNode *head;
	struct SingleNode *tail;
	int size;
}Queue;

Queue *queue_new(){
	Queue *q = (Queue*)malloc(sizeof(Queue));
	if(!q){
		printf("Bad allocation.\n");
		exit(EXIT_FAILURE);
	}
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

void queue_destroy(Queue *q){
	while(q->head){
		struct SingleNode *next = q->head->next;
		free(next);
		q->head = next;
	}
	free(q);
}

bool queue_empty(Queue *q){ return !q->size; }

int queue_size(Queue *q){ return q->size; }

int queue_back(Queue *q){
	if(queue_empty(q)){
		printf("Cannot get back of empty queue.\n");
		exit(EXIT_FAILURE);
	}
	return q->tail->data;
}

int queue_front(Queue *q){
	if(queue_empty(q)){
		printf("Cannot get front of empty queue.\n");
		exit(EXIT_FAILURE);
	}
	return q->head->data;
}

void queue_enqueue(Queue *q, int value){
	struct SingleNode *node = (struct SingleNode *)malloc(sizeof(struct SingleNode));
	if(!node){
		printf("Bad allocation.\n");
		exit(EXIT_FAILURE);
	}
	node->data = value;
	node->next = NULL;
	if(queue_empty(q)){
		q->head = node;
		q->tail = node;
	}
	else{
		q->tail->next = node;
		q->tail = node;
	}
	q->size++;
}

int queue_dequeue(Queue *q){
	if(queue_empty(q)){
		printf("Cannot dequeue an empty queue.\n");
		exit(EXIT_FAILURE);
	}
	struct SingleNode *temp = q->head;
	q->head = q->head->next;
	if(q->tail == temp)
		q->tail = q->head;
	int value = temp->data;
	free(temp);
	q->size--;
	return value;
}

void queue_debug(Queue *q){
	printf("Head at %p\n", (void*)q->head);
	printf("Tail at %p\n", (void*)q->tail);
	printf("Size is %d\n", q->size);
	struct SingleNode *current = q->head;
	while(current){
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n-----------------\n");
}

#endif