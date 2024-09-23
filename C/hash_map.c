//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// In this file we will implement a
// simple hash map with chaining to
// solve collisions. The hash
// function will map strings keys  
// using the division method
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//-----------------------------------
// Imports
//-----------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hash_map.h"

//-----------------------------------
// Main
//-----------------------------------
int main(int argc, char const *argv[]) {
	srand(time(NULL));
	Slot **map = create_hashmap();
	if(!map) exit(1);
	char *keys[NUM_OF_KEYS] = { 0 };
	for(int i = 0; i < NUM_OF_KEYS; i++) {
		keys[i] = create_random_key();
		Element *el = malloc(sizeof(Element));
		if(!el) exit(1);
		el->value = rand()%1000;
		el->key = keys[i];
		set(map, el->key, el);
		printf("element inserted - key: %s, value: %d\n", el->key, el->value);
	}
	printf("\ndeleting random elements\n");
	for(int i = 0; i < NUM_OF_KEYS; i++) {
		if(rand()%2) {
			int result =  delete(map, keys[i]);
			if(!result) printf("element deleted - key: %s\n", keys[i]);
		}
	}
	printf("\n");
	for(int i = 0; i < NUM_OF_KEYS; i++) {
		Element *el = get(map, keys[i]);
		if(el) printf("element found     - key: %s, value: %d\n", el->key, el->value);
		else   printf("element not found - key: %s\n", keys[i]);
	}
	free_map(map);
	for(int i = 0; i < NUM_OF_KEYS; i++)
		free(keys[i]);
    return 0;
}

//-----------------------------------
// Function definitions
//-----------------------------------
Slot **create_hashmap() {
	Slot **map = malloc(sizeof(Slot *) * MAP_SIZE);
	if(!map) return NULL;
	for(int i = 0; i < MAP_SIZE; i++) {
	    map[i] = NULL;
	}
	return map;
}

char *create_random_key() {
	int key_len = (rand()%(MAX_KEY_LEN)) + 1;
	char *key = malloc(sizeof(char) * (key_len + 1));
	key[key_len] = '\0';
	for(int i = 0; i < key_len; i++)
		key[i] = (char) 97 + rand()%26;
	return key;
}

int hash_key(char *key) {
	unsigned long long int result = 1;
	for(int c = 0; c < (int) strlen(key); c++) {
		result *= (int)key[c];
	}
	result = result%MAP_SIZE;
	return result;
}

int set(Slot **map, char *key, Element *el) {
	int index = hash_key(key);
	Slot *temp = map[index];
	Slot *slot = malloc(sizeof(Slot));
	if(!slot) return 1;
	slot->content = el;
	slot->next = temp;
	slot->prev = NULL;
	if(temp) temp->prev = slot;	
	map[index] = slot;
	return 0;
}

Element *get(Slot **map, char *key) {
	int index = hash_key(key);
	Slot *curr = map[index];
	while(curr && strcmp(curr->content->key, key))
		curr = curr->next;
	if(!curr) return NULL;
	return curr->content;
}

int delete(Slot **map, char *key) {
	int index = hash_key(key);
	Slot *curr = map[index];
	//Slot *prev = NULL;
	while(curr && strcmp(curr->content->key, key))
		curr = curr->next;
	if(!curr) return 1;
	if(curr->next) curr->next->prev = curr->prev;
	if(curr->prev) curr->prev->next = curr->next;
	else {
		if(!curr->next) map[index] = NULL;
		else map[index] = curr->next;
	}
	free(curr->content);
	free(curr);
	return 0;
}

int free_chain(Slot *chain) {
	if(!chain) return 1;
	Slot *curr = chain;
	if(curr->next) free_chain(curr->next);
	free(curr->content);
	free(curr);
	return 0;
}

int free_map(Slot **map) {
	if(!map) return 1;
	for(int i = 0; i < MAP_SIZE; i++)
		free_chain(map[i]);
	free(map);
	return 0;
}