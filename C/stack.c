//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// In this file we will implement a
// simple stack (LIFO structure) and
// it's basic functions, such as push
// and pop.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//-----------------------------------
// Imports
//-----------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//-----------------------------------
// Structs and typedefs
//-----------------------------------

typedef struct aux {
	int value;
	struct aux *next;
} Element;

typedef struct {
	Element *head;
	int size;
} Stack;


//-----------------------------------
// Function prototypes
//-----------------------------------
Stack *create_stack();
int push(Stack *s, int value);
int pop(Stack *s);
void print_stack(Stack *s);
void free_stack(Stack *s);

//-----------------------------------
// Main
//-----------------------------------
int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Stack *stack = create_stack();
	for(int i = 0; i < 10; i ++) {
		push(stack, rand()%1000);
		print_stack(stack);
	}
	for(int i = 0; i < 10; i ++) {
		pop(stack);
		print_stack(stack);
	}
	return 0;
}

//-----------------------------------
// Function definitions
//-----------------------------------
Stack *create_stack() {
	Stack *stack = malloc(sizeof(Stack));
	if(!stack) exit(1);
	*stack = (Stack) { 0 };
	return stack;
}

int push(Stack *s, int value) {
	Element *el = malloc(sizeof(Element));
	if(!el) return 1;
	el->value = value;

	if(s->size == 0) el->next = NULL;
	else el->next = s->head;
	s->head = el;
	s->size++;
	return 0;
}

int pop(Stack *s) {
	if(s->size == 0) return 1;
	Element *temp = s->head->next;
	free(s->head);
	s->head = temp;
	s->size--;
	return 0;
}

void print_stack(Stack *s) {
	Element *curr = s->head;
	printf("Stack [%d]: ", s->size);
	while(curr) {
		printf("%d ", curr->value);
		curr = curr->next;
	}
	printf("\n");
}
