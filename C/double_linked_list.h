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

//-----------------------------------
// Function prototypes
//-----------------------------------
List *create_list();
int insert_value(List *l, int value);
int remove_value(List *l, int value);
void print_list(List *l);
void free_list(List *l);

#endif