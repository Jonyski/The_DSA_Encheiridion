#ifndef BINARY_TREE_H
#define BINARY_TREE_H

//-----------------------------------
// Structs and typedefs
//-----------------------------------
typedef struct aux {
	int value;
	struct aux *left;
	struct aux *right;
	struct aux *parent;
} Node;

//-----------------------------------
// Function prototypes
//-----------------------------------
Node *create_bintree(int root_value);
Node *search(Node *r, int value);
int insert(Node *r, int value);
int delete(Node **r, int value);
Node *find_replacement(Node *r);
void print_bintree(Node *r);
void print_bintree_values(Node *r);
void free_bintree(Node *r);

#endif