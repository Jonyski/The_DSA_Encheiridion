#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

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
	int len;
} List;

#endif