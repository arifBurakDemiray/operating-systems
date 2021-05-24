//Arif Burak Demiray 
//This code is compiled with C99

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"

/**
 * This function tries to find an empty location for add operation
 * If not found returns null
 */ 
Node *find_empty_location(Node *node)
{
    Node *next = NULL;
    next = node->next;
    if (next == NULL)
    {
        return node;
    }
    else
    {
        return find_empty_location(node->next);
    }
}

int length(Node *first)
{
    int size = 0;
    Node *node = NULL;
    node = first;
    while (node != NULL)
    {
        size++;
        node = node->next;
    }
    return size;
}

void add_product(Node *first, product *new_data)
{
    if (first == NULL) //if list empty
    {   //malloc space for first element and make it first
        first = (Node *)malloc(sizeof(Node));
        first->data = new_data;
        first->before = NULL;
        first->next = NULL;
    }
    else
    {   //otherwise create a new node and find an empty space for it
        Node *new_node = malloc(sizeof(Node));
        new_node->data = new_data;
        new_node->before = NULL;
        new_node->next = NULL;
        Node *node = find_empty_location(first);
        if (node != NULL) //if found, set up links
        {
            node->next = new_node;
            new_node->before = node;
        }
        else
        {
            free(new_node);
            return;
        }
    }
}

/**
 * This function tries to find a node that contains specified product
 * If not found returns null
 */ 
Node *find_product(Node *node, product *data)
{
    if (node == NULL || node->data == NULL || data == NULL)
    {
        return NULL;
    }
    product *node_data = NULL;
    node_data = node->data;
    if (node_data == NULL)
        return NULL;
    if (equals(&node_data, &data) != 1)
    {
        return find_product(node->next, data);
    }
    else
    {
        return node;
    }
}

void remove_product(Node **first, product *data)
{

    Node *node = find_product(*first, data);
    if (node == NULL){ //if we come to end return
        return;
    }else{
        Node *next = NULL;  //set up temporary variables
        next = node->next;
        Node *before = NULL;
        before = node->before;
        int isHead = 0; //check for is head
        if (next != NULL && before != NULL){    //if node is between not null nodes
            before->next = next;
            next->before = before;
        }else if (before != NULL){  //if node at the end
            before->next = NULL;
        }else if (next != NULL){  //if node is the head
            Node *head = *first;    //take real address
            *first = (*first)->next;    //make first next node of the head
            (*first)->before = NULL;    //make before null
            free(head); //and free head
            isHead = 1; //make flag true
        }else{
            return;
        }
        if (!isHead)    //free removed and links' broke node
        {
            free(node);
            node = NULL;
        }
    }
}

void free_list(Node *first)
{
    Node *node = first;
    if (first == NULL)
    {
        return; //if empty return
    }
    Node *next = NULL;
    do
    {
        next = node->next;
        free(node);
        node = next;
    } while (next != NULL); //while hasNext
}

void print_list(Node *first)
{
    Node *node = NULL;
    node = first;
    if (node == NULL)
    {
        return;
    }
    while (node != NULL)    //while hasNext
    {
        product *data = NULL;
        data = node->data;
        to_string(data);
        node = node->next;
    }
}

product *find_product_by_type(Node *node, char *type)
{
    if (node == NULL || type == NULL || node->data == NULL)
    {   //if one of the datas is null, return
        return NULL;
    }
    if (type_equals(node->data, type) != 1) //if types are not matched
    {
        return find_product_by_type(node->next, type);
    }
    else
    {
        return node->data;
    }
}

product *get(Node *first, int index)
{
    int len = length(first);
    if (first == NULL || first->data == NULL || index >= len)
    {
        return NULL;
    }
    Node *temp = NULL;
    temp = first;
    int i = 0;
    while (temp != NULL)    //while has next
    {
        if (index == i) //if given index matches
            return temp->data;
        temp = temp->next;
        i++;
    }
}

void print_list_bound(Node *first, int budget)
{

    Node *node = NULL;
    node = first;
    if (node == NULL)
    {
        return;
    }
    while (node != NULL)
    {
        product *data = NULL;
        data = node->data;
        if (data->price <= budget)  //if given bound greater than or equal to product's price
        {
            to_string(data);
        }
        node = node->next;
    }
}