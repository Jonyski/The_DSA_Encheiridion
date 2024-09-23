//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// In this file we will define a
// dynanic double linked list with a
// head and a tail, and some basic
// operation to manipulate it.
// PS: the list will be ordered
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//-----------------------------------
// Imports
//-----------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "double_linked_list.h"

//-----------------------------------
// Main
//-----------------------------------
int main(int argc, char const *argv[])
{
	srand(time(NULL));
	List *list1 = create_list();
	// populating the list with random numbers
	for(int i = 0; i < 10; i ++) {
		insert_value(list1, rand()%1000);
		print_list(list1);
	}
	// removing elements from it randomly
	Element *curr = list1->head->next;
	while(curr != list1->tail) {
		curr = curr->next;
		if(rand() % 2 == 1) {
			remove_value(list1, curr->prev->value);
			print_list(list1);
		}
	}
	free_list(list1);
	return 0;
}

//-----------------------------------
// Function definitions
//-----------------------------------
List *create_list() {
	// creating head and tail
	Element *head = malloc(sizeof(Element));
	Element *tail = malloc(sizeof(Element));
	if(!head || !tail) exit(1);
	*head = (Element) { 0 };
	*tail = (Element) { 0 };
	// creating list
	List *list = malloc(sizeof(List));
	if(!list) exit(1);
	list->len = 0;
	// linking it all together
	list->head = head;
	list->tail = tail;
	head->next = tail;
	tail->prev = head;
	return list;
}

int insert_value(List *l, int value) {
	// creating a new element
	Element *el = malloc(sizeof(Element));
	if(!el) return 1;
	el->value = value;
	// finding the place where to insert it
	Element *target = l->head;
	while(target->next->value < value && target->next != l->tail)
		target = target->next;
	// inserting it
	el->prev = target;
	el->next = target->next;
	target->next = el;
	el->next->prev = el;
	l->len++;
	return 0;
}

void print_list(List *l) {
	printf("Lista [%d]: ", l->len);
	Element *curr = l->head->next;
	while(curr != l->tail) {
		printf("%d ", curr->value);
		curr = curr->next;
	}
	printf("\n");
}

int remove_value(List *l, int value) {
	// finding the element with the given value
	Element *target = l->head->next;
	while(target->value != value && target != l->tail)
		target = target->next;
	if(target == l->tail) return 1;
	// updating it's neighbors pointers
	target->prev->next = target->next;
	target->next->prev = target->prev;
	// freeing it
	free(target);
	l->len--;
	return 0;
}

void free_list(List *l) {
	Element *curr = l->head;
	while(curr) {
		Element *temp = curr->next;
		free(curr);
		curr = temp;
	}
	free(l);
}