//Arif Burak Demiray 
//This code is compiled with C99

#include "product.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int equals(product *src, product *dst)
{
    int result = 0;  //result of compare operation
    if (src == NULL || dst == NULL)  //if one of them null return
        return result;
    if (src->product_name == NULL || dst->product_name == NULL)
        return result;  //if one of the attributes null return
    if (src->product_type == NULL || dst->product_type == NULL)
        return result;

    if (strcmp(src->product_name, dst->product_name) == 0) 
    {//if names are equal
        if (strcmp(src->product_type, dst->product_type) == 0)
        {//if types are equal
            result = 1;
        }
    }

    return result;
}

int type_equals(product *src, char *type)
{
    int result = 0;
    if (src == NULL || type == NULL)
        return result;
    char *src_type = src->product_type;
    if (src_type == NULL)
    {
        return result;
    }
    if (strcmp(src_type, type) == 0) //if types are equal
    {
        result = 1;
    }
    return result;
}

void to_string(product *product)
{
    char *prName = " ";
    prName = product->product_name;
    char *prType = " ";
    prType = product->product_type;
    int prPrice = 0;
    prPrice = product->price;
    printf("product_name: %s, product_type: %s, price: %d \n", prName, prType, prPrice);
}

//this function initializes a product
product init_prd()
{
    product pr = {" ", " ", 0};
    return pr;
}

product Product(char *name, char *type, int price)
{
    product pr = init_prd();
    copy(pr.product_name, name, size(name));//copy size and type arrays
    copy(pr.product_type, type, size(type));
    pr.price = price;
    return pr;
}

void free_product_list(product *products, int len)
{
    int i = 0;
    for (i; i < len; i++)
    {//free products
        free(&products[i]);
    }
}