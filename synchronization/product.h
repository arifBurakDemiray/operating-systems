//Arif Burak Demiray 
//This code is compiled with C99
#ifndef PRODUCT_H //include guard
#define PRODUCT_H

typedef struct product
{
    char product_name[30]; // (phone, tshirt, coke etc.)
    char product_type[30]; //(electronicDevice, clothing, market etc.)
    int price;             // (can be integer between 1-1000)
} product;

/**
 * This function compares two products
 * If their name and type equals returns 1 
 * If one of them not equals returns 0
 * This function uses strcmp two compare two char arrays
 */
int equals(product *source, product *destination);

/**
 * This function compares a product's type with given type char array
 * If they are equals returns 1 otherwise 0
 */
int type_equals(product *src, char *type);

//This function prints string value of a product
void to_string(product *product);

/**
 * This function creates a product with given attributes
 * name is the name of the product
 * type is the type of the product
 * price is the price of the product
 */ 
product Product(char *name, char *type, int price);

/**
 * This function free a list of products
 */ 
void free_product_list(product *products, int size);

#endif /*PRODUCT_H*/