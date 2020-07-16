#include <stdbool.h>

#ifndef __QUEUE_ARRAY_H__
#define __QUEUE_ARRAY_H__

typedef struct queueImplementation{
	int *data;
	int start;
	int size;
	int capacity;
}Queue;

Queue *queue_new(int capacity){
	Queue *q = (Queue *)malloc(sizeof(Queue));
	if(!q){
		printf("Bad allocation.\n");
		exit(EXIT_FAILURE);
	}
	q->capacity = capacity;
	q->data = (int *)malloc(sizeof(int)*q->capacity);
	if(!q->data){
		printf("Bad allocation.\n");
		exit(EXIT_FAILURE);
	}
	q->size = 0;
	q->start = 0;
	
	return q;
}

void queue_destroy(Queue *q){
	free(q->data);
	free(q);
}

bool queue_empty(Queue *q){ return !q->size; }

bool queue_full(Queue *q){ return q->size == q->capacity; }

int queue_back(Queue *q){
	if(queue_empty(q)){
		printf("Cannot get back of empty queue.\n");
		exit(EXIT_FAILURE);
	}
	return *(q->data + (q->start + q->size-1) % q->capacity);
}

int queue_front(Queue *q){
	if(queue_empty(q)){
		printf("Cannot get front of empty queue.\n");
		exit(EXIT_FAILURE);
	}
	return *(q->data + q->start);
}

void queue_enqueue(Queue *q, int value){
	if(queue_full(q)){
		printf("Cannot enqueue a full queue.\n");
		exit(EXIT_FAILURE);
	}
	*(q->data+(q->start+q->size++)%q->capacity) = value;
}

int queue_dequeue(Queue *q){
	if(queue_empty(q)){
		printf("Cannot dequeue an empty queue.\n");
		exit(EXIT_FAILURE);
	}
	int temp = queue_front(q);
	q->start = (q->start + 1) % q->capacity;
	q->size--;
	return temp;
}

#endif