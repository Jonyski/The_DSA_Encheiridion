//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// In this file we will implement a
// queue (FIFO structure) and it's
// basic functions, such as enqueue
// and dequeue
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//-----------------------------------
// Imports
//-----------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

//-----------------------------------
// Main
//-----------------------------------
int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Queue *queue = create_queue();
	for(int i = 0; i < 10; i ++) {
		enqueue(queue, rand()%1000);
		print_queue(queue);
	}
	for(int i = 0; i < 10; i ++) {
		dequeue(queue);
		print_queue(queue);
	}
	free_queue(queue);
	return 0;
}

//-----------------------------------
// Function definitions
//-----------------------------------
Queue *create_queue() {
	Element *head = malloc(sizeof(Element));
	Element *tail = malloc(sizeof(Element));
	if(!head || !tail) exit(1);
	*head = (Element) { 0 };
	*tail = (Element) { 0 };
	Queue *queue = malloc(sizeof(Queue));
	if(!queue) exit(1);
	queue->head = head;
	queue->tail = tail;
	head->next = tail;
	tail->prev = head;
	queue->size = 0;
	return queue;
}

int enqueue(Queue *q, int value) {
	Element *el = malloc(sizeof(Element));
	if(!el) return 1;
	el->value = value;
	el->prev = q->tail->prev;
	el->next = q->tail;
	q->tail->prev->next = el;
	q->tail->prev = el;
	q->size++;
	return 0;
}

int dequeue(Queue *q) {
	if(q->size == 0) return 1;
	Element *temp = q->head->next;
	q->head->next = temp->next;
	temp->next->prev = q->head;
	free(temp);
	q->size--;
}

void print_queue(Queue *q) {
	printf("queue [%d]: ", q->size);
	Element *curr = q->head->next;
	while(curr != q->tail) {
		printf("%d ", curr->value);
		curr = curr->next;
	}
	printf("\n");
}

void free_queue(Queue *q) {
	Element *curr = q->head;
	while(curr) {
		Element *temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(q);
}