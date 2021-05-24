//Arif Burak Demiray - 250201022
//This code compiled with C99

#include "../models/product.h"
#include "../models/dynamic_array.h"
#include "operations.h"
#include <stdlib.h>
#include <stdio.h>

//this function creates initial product list
Product* generate_products(){
    Product bread,egg,pasta,
        fish,milk,water,hand,tooth,pizza,choco;
    bread = product("Bread",10,3.5);
    egg = product("Egg",30,2.82);
    pasta = product("Pasta",15,2.79);
    fish = product("Fish",25,15.98);
    milk = product("Milk",10,10.26);
    water = product("Water Small",35,1.55);
    hand = product("Hand Sanitizer",20,20.55);
    tooth = product("Toothpaste",15,10.83);
    pizza = product("Pizza",10,15.30);
    choco = product("Chocolate",40,5.21);
    Product *products = malloc(10*sizeof(Product)); //take space for array
    products[0] = bread;
    products[1] = egg; 
    products[2] = pasta; 
    products[3] = fish; 
    products[4] = milk; 
    products[5] = water; 
    products[6] = hand; 
    products[7] = tooth; 
    products[8] = pizza; 
    products[9] = choco; 
    return products;    //return it
}

//this function lists products and returns the total cost of a list
double list_products(Product *list,int size){
    double total = 0;   //take size
    for(int i=0;i<size;i++){
        if(list[i].quantity >= 1)   //only print quantity greater than or equal 1 ones
            total+=to_string(&list[i]); //increase total and write it
    }
    return total;   //return total
}

//this function searchs a given name in shop list and updates user list
//upTo again for finding size of product lists
void search_product(Product* listShop,Product* listUser, Array* name,int quantity,int upTo){
    int i=0;    //loop variable
    int flag = 1;   //flag is for product is found,not found or not have enough quantity
    int listSize = upTo; //size of shop list
    Product* temp;  //found product to update user list
    for(i;i<listSize;i++){            
        if(match(name,listShop[i].name)){       //if name matches with product name
            if(listShop[i].quantity >= quantity){   //if we have enough quantity 
                update_quantity(&listShop[i],-quantity);  //update shop quantity
                printf("You bought %d %s(s)!\n",quantity,listShop[i].name);    //print information
                temp = &listShop[i];  //make found this product
                flag = 0;  //make flag 0 to indicate found
                break;   //and break the loop
            }else{
                temp = &listShop[i];  //else make temp found
                flag=-1;    //but indicate flag as -1 to not have enough quantity
            }
        }
    }
    if(flag==-1){
        printf("There is not enough %s.\n\n",temp->name);  //not enough quantity
        return; //finish function
    }
    if(flag){   //if flag not changed during loop means not found 
        printf("Product not found!\n\n");
    }
    else{//product found
        flag = 1; //make flag 1 again to if user has this product or bought first time
        i=0;   //reset loop variable
        Array userProduct;  //user product name
        listSize = size_of_product_list(listUser,upTo);  //user products list size
        for(i;i<listSize;i++){
            userProduct = array(listUser[i].name);  //make product name a dynamic array
            if(match(&userProduct,temp->name)){  //if matches with found 
                update_quantity(&listUser[i],quantity); //update quantity of user product list
                flag=0; //make flag 0 to indicate found
            }
        }
        if(flag){ //if not found in user product list
            listUser[i] = product(temp->name,quantity,temp->price); //create a product for user
            printf("You purchased %s first time!\n\n",temp->name); //and inform user
        }
        else{   //else we found in user list and inform user
            printf("%s quantity updated succesfully!\n\n",temp->name);
        }
    }
}

//this function is for menu operation 1, takes dynamic array and lists from upper level
void buy_product(Product* products, Product* userProducts, Array* input){
    char enteredValue[100]; //input
    printf("Name of Product: ");  
    fgets(enteredValue, 100, stdin);   //fgets upto 100 char
    Array temp = array(enteredValue);  //create dynamic array from input
    if(!set(input,&temp))  //if can not be set means above 50 chars
        printf("You can not enter name above 50 chars\n\n");
    else{   
        printf("Quantity of Product: ");
        fgets(enteredValue, 100, stdin);    //take quantity from user
        int quantity = to_int(enteredValue); //convert it to integer
        if(quantity!=-1)    //if converted successfuly
            search_product(products,userProducts,input,quantity,10); //search for product upTo 10 elements
        else
            printf("Please enter a valid number.\n\n");  //else quantity is not number
    }
}

//this is program function, gathers all thing
void program(){
    Product* products = generate_products();  //shop list
    Product userProducts[10] = {}; //user list up to 10 products
    Array input = initalize();  //init dynamic array
    char number[5]; //for menu inputs
    printf("\nWelcome to the program\n\n"); //prints for instructions
    printf("-----MAIN MENU-----\n");
    printf("1- Buy a product\n");
    printf("2- List all products\n");
    printf("3- Shopping summary\n");
    printf("4- Exit\n");
    printf("-------------------\n\n");
    int endWhile = 1;  //loop controller
    while(endWhile){
        printf("Enter the choice:");
        fgets(number,5,stdin);  //get the menu inpur
        if(number[1]=='\n' | size(number)<2){  //if it is one sized digit
        if(number[0]=='1'){ //if 1 buy a product
            buy_product(products,userProducts,&input);
            }
        else if(number[0]=='2'){  //if 2 list all existing products
            printf("----------- Product List -----------\n");
            list_products(products,10);
            printf("-------------------------------------\n\n");}
        else if(number[0]=='3'){  //if 3 list bought products
            int sizeOfUse = size_of_product_list(userProducts,10);
            if(sizeOfUse >= 1){
                printf("----------- Product List -----------\n");
                double total = list_products(userProducts,sizeOfUse);
                printf("-------------------------------------\n");
                printf("Total price: %.2f\n\n",total);}
            else  //if there is no product in the user list
                printf("There is no product in the list!\n\n");}
        else if(number[0]=='4'){ //exit 
            printf("See you again\n\n");
            delete(&input); //delete dynamic array
            endWhile = 0;} //loop finished
        else
            printf("Invalid input plase try again\n\n");
        }
         else
            printf("Please enter only one digit\n\n");
        }
    free(products); //free product list
}

