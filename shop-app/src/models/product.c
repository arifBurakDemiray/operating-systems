//Arif Burak Demiray - 250201022
//This code compiled with C99

#include "product.h"
#include <stdio.h>
#include "dynamic_array.h"

//takes name, quantity and price of a product and creates it
Product product(char* name,int quantity,double price){
    Product product;        //product
    product.name=name;      //create name
    product.price=price;    //create price
    product.quantity=quantity;      //create quantity
    return product;     //return it
}

//updates a product's quantity by given integer value
void update_quantity(Product* product,int quantity){
    product->quantity+=quantity;    //update quantity of product
}

double to_string(Product* product){                                 //print string value of a product
    printf("Product name:%s,Unit price:%.2f,Quantity:%d\n",product->name,product->price,product->quantity);
    return product->price*product->quantity; //calculate cost and return it
}

//calculates size of a product list by given range
int size_of_product_list(Product *products, int upTo){
    int i = 0;      //loop number
    int size = 0;   //size number
    for(i;i<upTo;i++){  //taken range value
        if(products[i].quantity>=1){    //if product's quantity is greater than or  
            size++;}                   //equal to 1 which means we have this product
    }       //increase size
    return size;    //return size

}