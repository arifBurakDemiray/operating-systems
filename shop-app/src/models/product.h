//Arif Burak Demiray - 250201022
//This code compiled with C99

#ifndef PRODUCT_H //include guard
#define PRODUCT_H

typedef struct Product  //Product struct
{
    int quantity;       //quantity
    char* name;         //name
    double price;       //price of a product

}Product;

Product product(char* name,int quantity,double price);  //constructor for product

void update_quantity(Product* product,int quantity);    //updates quantity of a product

double to_string(Product* product);  //converts a product struct to printf
                                    // and calculates total cost for a product
int size_of_product_list(Product *products, int upTo);  //calculates size of a product by given range

#endif /* PRODUCT_H */

