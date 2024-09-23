#ifndef QUEUE_H
#define QUEUE_H

//-----------------------------------
// Structs and typedefs
//-----------------------------------
typedef struct aux {
	int value;
	struct aux *next;
	struct aux *prev;
} Element;

typedef struct {
	Element *head;
	Element *tail;
	int size;
} Queue;

//-----------------------------------
// Function prototypes
//-----------------------------------
Queue *create_queue();
int enqueue(Queue *q, int value);
int dequeue(Queue *q);
void print_queue(Queue *q);
void free_queue(Queue *q);

#endif