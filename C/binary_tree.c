//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// In this file we will implement a
// binary tree and some of it's main
// algorithms, such as insertion,
// deletion and search
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//-----------------------------------
// Imports
//-----------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_tree.h"

//-----------------------------------
// Main
//-----------------------------------
int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Node *tree = create_bintree(84);
	print_bintree(tree);
	int values_inserted[20] = { 0 }; // just for testing purposes
	values_inserted[0] = tree->value;
	
	for(int i = 1; i < 20; i++) {
		int v = rand()%1000;
		insert(tree, v);
		print_bintree(tree);
		values_inserted[i] = v;
	}
	printf("\ndeleting random elements\n");
	for(int i = 0; i < 20; i++) {
		if(rand()%2) {
			delete(&tree, values_inserted[i]);
			print_bintree(tree);
		}
	}
	free_bintree(tree);
	return 0;
}

//-----------------------------------
// Function definitions
//-----------------------------------
Node *create_bintree(int root_value) {
	Node *root = malloc(sizeof(Node));
	if(!root) exit(1);
	*root = (Node) { 0 };
	root->value = root_value;
	return root;
}

Node *search(Node *r, int value) {
	if(!r) return NULL;
	if(r->value == value) {
		return r;
	} else if(r->value > value) {
		if(!r->left) return NULL;
		return search(r->left, value);
	} else {
		if(!r->right) return NULL;
		return search(r->right, value);
	}
}

int insert(Node *r, int value) {
	// blocking repeated values
	if(r->value == value) return 1;

	if(value < r->value) {
		if(r->left)
			insert(r->left, value);
		else {
			Node *el = malloc(sizeof(Node));
			if(!el) return 1;
			*el = (Node) { 0 };
			el->value = value;
			el->parent = r;
			r->left = el;
		}
	} else {
		if(r->right)
			insert(r->right, value);
		else {
			Node *el = malloc(sizeof(Node));
			if(!el) return 1;
			*el = (Node) { 0 };
			el->value = value;
			el->parent = r;
			r->right = el;
		}
	}
	return 0;
}

int delete(Node **r, int value) {
	if(!(*r)) return 1;
	Node *el = search(*r, value);
	if(!el) return 1;
	// the node being removed has no children
	if(!el->right && !el->left) {
		if(!el->parent) {
			*r = NULL;
			free(el);
			return 0;
		}
		if (el->parent->left == el)
			el->parent->left = NULL;
		else if(el->parent->right == el)
			el->parent->right = NULL;
		free(el);
		return 0;
	}
	// the node being removed has only the right child
	if(!el->left && el->right) {
		if(!el->parent) {
			*r = el->right;
			el->right->parent = NULL;
			free(el);
			return 0;
		}
		if (el->parent->left == el)
			el->parent->left = el->right;
		else if(el->parent->right == el)
			el->parent->right = el->right;
		el->right->parent = el->parent;
		free(el);
		return 0;
	}
	// the node being removed has only the left child
	if(el->left && !el->right) {
		if(!el->parent) {
			*r = el->left;
			el->left->parent = NULL;
			free(el);
			return 0;
		}
		if (el->parent && el->parent->left == el)
			el->parent->left = el->left;
		else if(el->parent && el->parent->right == el)
			el->parent->right = el->left;
		el->left->parent = el->parent;
		free(el);
		return 0;
	}
	// the node being removed has both children
	Node *repl = find_replacement(el);
	// link the parent to the replacement element
	if(el->parent) {
		if(el->parent->left == el)
			el->parent->left = repl;
		else if(el->parent->right == el)
			el->parent->right = repl;
	} else *r = repl;
	// re-link the replacement parent to the replacement left-child
	if (repl->parent != el) {
	    if(repl->parent->right == repl) {
	        repl->parent->right = repl->left;
	    } else if(repl->parent->left == repl) {
	        repl->parent->left = repl->left;
	    }
	    if(repl->left) {
	        repl->left->parent = repl->parent;
	    }
	}
	// make the replacement connect to the nodes el connected to
	if(el->left && el->left != repl) el->left->parent = repl;
	if(el->right) el->right->parent = repl;
	repl->right = el->right;
	repl->left = el->left == repl ? repl->left : el->left;
	repl->parent = el->parent;
	free(el);
	return 0;
}

Node *find_replacement(Node *r) {
	// finding the right-most node in the left sub-tree
	Node *curr = r->left;
	while(curr->right) curr = curr->right;
	return curr;
}

void print_bintree(Node *r) {
	printf("binary tree values: ");
	print_bintree_values(r);
	printf("\n");
}

void print_bintree_values(Node *r) {
	if(r) {
		if(r->left) print_bintree_values(r->left);
		printf("%d ", r->value);
		if(r->right) print_bintree_values(r->right);
	}
}

void free_bintree(Node *r) {
	if(r) {
		if(r->left) free_bintree(r->left);
		if(r->right) free_bintree(r->right);
		if(r->parent && r->parent->right == r) r->parent->right = NULL;
		if(r->parent && r->parent->left == r) r->parent->left = NULL;
		free(r);
	}
}