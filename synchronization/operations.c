//Arif Burak Demiray 
//This code is compiled with C99

#include "operations.h"
#include <stdio.h>
#include <stdlib.h>

int find_random_index(int indices[], int len)
{
    int size = 0;
    size = len;
    int index = 0;
    do{
        index = rand_int(size);
    } while (indices[index]); //if a random index no chosen by random it breaks the loop
    indices[index] = 1; //make found indices to found this index
    return index; //and return it
}

void increase_random(Node *head, int list_num)
{
    int len = length(head); //gets lengt of the list
    if (len < 1) //if list is empty
        return; //return from function
    int index = rand_int(len); //choose a random index
    product *pr = NULL;
    pr = get(head, index); 
    if (pr == NULL)
        return;
    if (pr->price < 1)  //if coming one's price is lower than 1
        return;

    int old_price = pr->price;
    pr->price += old_price / 5;//update price
    printf("-----------------------------------------------------------------------\nProduct price increased in ");
    if (list_num == 1){ //print list name
        printf("Products 1: ");
    }else if (list_num == 2){
        printf("Products 2: ");
    }else{
        printf("Favorites: ");
    }
    printf("%s, %d\n-----------------------------------------------------------------------\n", pr->product_name, pr->price);
}

int rand_int(int range)
{
    return (rand() % range);
}