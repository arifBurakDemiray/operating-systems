//Arif Burak Demiray 
//This code is compiled with C99

#ifndef OPERATIONS_H //include guard
#define OPERATIONS_H

#include "linked_list.h"

/**
 * This function creates a random integer number by given range
 * starts from 0
 */ 
int rand_int(int range);

/**
 * This function increases a product's price by %20 by given list number
 * list number are 1,2,3. 1 and 2 for products lists, 3 is favorites list
 */
void increase_random(Node *head, int list_num);

/**
 * This function tries find unique random index to choose different product
 */ 
int find_random_index(int indices[], int len);

#endif /*OPERATIONS_H*/