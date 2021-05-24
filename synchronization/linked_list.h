//Arif Burak Demiray 
//This code is compiled with C99

#include "product.h"

#ifndef LINKED_LIST_H //include guard
#define LINKED_LIST_H
//this is a two way linked list
typedef struct Node
{
    struct Node *next;
    struct Node *before;
    struct product *data;
} Node;

/**
 * This function adds a product to end of the list
 */ 
void add_product(Node *first, product *new_data);

/**
 * This function removes a product from the list
 */ 
void remove_product(Node **first, product *data);

/**
 * This function gets length of the list
 */ 
int length(Node *first);

/**
 * This function frees nodes of a linked list
 */ 
void free_list(Node *first);

/**
 * This function prints the contents of a linked list
 */ 
void print_list(Node *first);

/**
 * This function finds a product by a given type
 * If not found returns null
 */ 
product *find_product_by_type(Node *node, char *type);

/**
 * This function gets an element by its index
 * If not found returns null
 */ 
product *get(Node *first, int index);

/**
 * This function prints a linked list by given budget
 */ 
void print_list_bound(Node *first, int budget);

#endif /*LINKED_LIST_H*/