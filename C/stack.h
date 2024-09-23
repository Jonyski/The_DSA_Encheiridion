#ifndef STACK_H
#define STACK_H

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

#endif