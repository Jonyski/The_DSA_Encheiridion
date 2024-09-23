#ifndef HASH_MAP_H
#define HASH_MAP_H

//-----------------------------------
// Structs, typedefs and defines
//-----------------------------------
#define MAP_SIZE 3
#define NUM_OF_KEYS 10
#define MAX_KEY_LEN 32

typedef struct {
	char *key;
	int value;
} Element;

typedef struct aux {
	Element *content;
	struct aux *next;
	struct aux *prev;
} Slot;

//-----------------------------------
// Function prototypes
//-----------------------------------
Slot **create_hashmap();
char *create_random_key();
int hash(char *key);
int set(Slot **map, char *key, Element *el);
Element *get(Slot **map, char *key);
int delete(Slot **map, char *key);
int free_chain(Slot *chain);
int free_map(Slot **map);


#endif