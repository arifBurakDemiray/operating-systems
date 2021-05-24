//Arif Burak Demiray 
//This code is compiled with C99

#include "operations.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#define THREAD_COUNT 4  //thread count for the program
#define FIRST_LIST 1    //first list number
#define SECOND_LIST 2   //second list number

Node *prlist_first = NULL;  //first product list
Node *prlist_second = NULL;  //second product list
Node *favlist = NULL;   //favories list

char type[30] = {};   //input of type
int budgetVar = 0;  //input of budget
int list_number = 0;  //list num for type2 thread to which list is going to be took

int S = 0;  //semaphore for entering a thread
int S_LAST = 0; //semaphore for a round , a round is consist of 4 thread
int S_FINISH = 1;   //semaphore for closing threads
int S_LOOP = 1;  //semaphore for waiting all threads to start at the same time
int S_WAIT = 1;  //semaphore for holding all threads to finish up and start at the same time all threads

/**
 * This function moves two products by given type
 */ 
int move(Node **list, char *type)
{   product *found = NULL
;   int i = 0
;   for (i; i < 2; i++){
        found = find_product_by_type((*list), type)
;       if (found == NULL)
            break
;       else{
            remove_product(list, found)
;           add_product(&favlist, found)
;       
        }
    }
    return i; //it returns how many products are moved to favorites
}

/**
 * This function is the type 1 thread's function
 */ 
void *cut_paste(void *args)
{
    while (S_FINISH)//while program runs
    {
        while(S_LOOP);//wait for all to start
        if(!S_FINISH){//if program finished break the main loop
            break;
        }
        printf("!!! Type 1 thread is running...\n");
        pthread_mutex_lock(&mutex); //lock mutex
        if (S){ //if enter semaphore is already taken, wait for it until someone releases it
            pthread_cond_wait(&cond, &mutex);
        }
        S++;//increase to demonstrate that it entered
        int list_no = (int)args; //given list number
        int result = 0; //result for move function
        if (list_no % 2 == 0){ //if modulo of number is 0 by 2, means it should process on second list
            result = move(&prlist_second, type); 
        }else{ //otherwise first list
            result = move(&prlist_first, type);
        }
        if (result != 0){ // if any product moved print information
            printf("-----------------------------------------------------------------------\n%d product(s) is cut from ", result);
            if (list_no % 2 == 0){
                printf("Products 2 ");
            }else{
                printf("Products 1 ");
            }
            printf("and pasted to favorites\n-----------------------------------------------------------------------\n");
        }
        S_LAST++; //increase S last for main function
        S--; //exit from semaphore
        pthread_cond_signal(&cond);  //signal next waiting
        pthread_mutex_unlock(&mutex); //unlock mutex
        printf("!!! Type 1 thread is exited...\n");
        while(S_WAIT); //and wait other thread types to done their process for that round
    }
}

/**
 * This is the type 2 thread's function
 */ 
void *increase_price(void *args)
{
    while (S_FINISH) //while program runs
    {
        while(S_LOOP); //wait for all
        if(!S_FINISH){
            break;
        }
        printf("!!! Type 2 thread is running...\n");
        pthread_mutex_lock(&mutex); //lock mutex
        if (S){ //wait for entered ones to finish its work
            pthread_cond_wait(&cond, &mutex);
        }
        S++;
        if (list_number == 1){
            increase_random(prlist_first, list_number);
        }else if (list_number == 2){
            increase_random(prlist_second, list_number);
        }else{
            increase_random(favlist, list_number);
        }
        S_LAST++; //increase S last to say that thread number's are increasing to THREAD_COUNT
        S--;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        printf("!!! Type 2 thread is exited...\n");
        while(S_WAIT);
    }
}

/**
 * This function is for type 3 thread
 */ 
void *print_purchasable(void *args)
{
    while (S_FINISH)
    {
        while(S_LOOP);
        if(!S_FINISH){                         //Why wait for THREAD_COUNT - 1?
            break;                            //because type 3 thread must work after type 1 and type 2  
        }                                    //if there is new product moved we should show
        while (S_LAST != THREAD_COUNT - 1); //if a product's price we should show new price
        printf("!!! Type 3 thread is running...\n");
        int lenFav = length(favlist); //get favlist's len
        if (budgetVar < 1 || lenFav < 1){ //if fav list is empty or given budget less then 1
            printf("-----------------------------------------------------------------------\n");
            printf("You can not buy anything\n");
            printf("-----------------------------------------------------------------------\n");
            return; //why am I returning from here, because no sync variables are touched by this function,
        }           // so it is safe to return

        pthread_mutex_lock(&mutex);
        if (S){
            pthread_cond_wait(&cond, &mutex);
        }
        S++;
        printf("-----------------------------------------------------------------------\nYou can buy produtcs which are lower price than your budget: %d\n", budgetVar);
        print_list_bound(favlist, budgetVar); //print list by given budget
        printf("-----------------------------------------------------------------------\n");
        S--;
        S_LAST++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        printf("!!! Type 3 thread is exited...\n");
        while(S_WAIT);
    }
}

/**
 * This function distributes products randomly to
 * products 1 and products 2 lists
 */ 
void put_random(product *products, int size)
{
    int len = 0;
    len = size;
    int indices[len];
    for (int i = 0; i < len; i++){
        indices[i] = 0; //init found indices
    }
    for (int i = 0; i < len; i++){
        int index = find_random_index(indices, len);
        if (i % 2 == 0){ //it distributes products one by one to lists
            add_product(&prlist_first, &products[index]);
        }else{
            add_product(&prlist_second, &products[index]);
        }
    }
}

int main()
{
    srand(time(0));
    product pr1 = Product("samsung_S5", "electronic", rand_int(1000) + 1);
    product pr2 = Product("soap", "market", rand_int(1000) + 1);
    product pr3 = Product("shower_jel", "market", rand_int(1000) + 1);
    product pr4 = Product("cacao_biscuit", "market", rand_int(1000) + 1);
    product pr5 = Product("huawei_tablet", "electronic", rand_int(1000) + 1);
    product pr6 = Product("dress", "clothing", rand_int(1000) + 1);
    product pr7 = Product("tshirt", "clothing", rand_int(1000) + 1);
    product pr8 = Product("jean", "clothing", rand_int(1000) + 1);
    product pr9 = Product("monitor", "electronic", rand_int(1000) + 1);
    product pr0 = Product("shoes", "clothing", rand_int(1000) + 1);
    product products[10];
    products[0] = pr1;
    products[1] = pr2;
    products[2] = pr3;
    products[3] = pr4;
    products[4] = pr5;
    products[5] = pr6;
    products[6] = pr7;
    products[7] = pr8;
    products[8] = pr9;
    products[9] = pr0;
    put_random(products, 10);
    //init products and distribute products

    printf("Welcome to the program, All lists are set up, you can start now...\n");

    char budget[30] = {};   //budget input buffer

    pthread_t threads[THREAD_COUNT];  //create threads

    pthread_create(&threads[0], NULL, cut_paste, FIRST_LIST);  

    pthread_create(&threads[1], NULL, cut_paste, SECOND_LIST);

    pthread_create(&threads[2], NULL, increase_price, NULL);

    pthread_create(&threads[3], NULL, print_purchasable, NULL);

    do
    {
        printf("-|-|-|-|-|-|-|-|-|-|-|-\n");
        printf("Type of Product: ");
        fgets(type, 30, stdin);
        type[strcspn(type, "\n")] = 0;
        printf("-|-|-|-|-|-|-|-|-|-|-|-\n");
        printf("Your budget: ");
        fgets(budget, 30, stdin);
        printf("-|-|-|-|-|-|-|-|-|-|-|-\n");
        budget[strcspn(budget, "\n")] = 0;
        //take inputs and eliminate newline
        budgetVar = to_int(budget); //convert budget to integer

        list_number = rand_int(3) + 1;  //create random list number for thread type 2

        if (budgetVar == -1){   //if budget can not be converted 
            printf("You should enter a valid budget. It should be a positive integer\n");
        }else{
            S_WAIT = 1; //make wait 1 to freeze all threads after they done their job
            S_LOOP = 0; //start all threads
            
            while (S_LAST != THREAD_COUNT); //wait all threads to finish up their job
            S_LAST = 0; //reset last semaphore

            //print lists' contents
            printf("############################################\n");
            printf("Products 1:\n");
            print_list(prlist_first);
            printf("############################################\n");
            printf("Products 2:\n");
            print_list(prlist_second);
            printf("############################################\n");
            printf("Favorites:\n");
            print_list(favlist);
            printf("############################################\n");

            S_WAIT = 0; //now start next round for all thread
            S_LOOP = 1; //and wait them to start at the same time
        }
    } while (length(prlist_second) != 0 || length(prlist_first) != 0);  
    // if products lists are empty 
    S_FINISH = 0;  //make finish semaphore 0 to exit from all threads
    S_LOOP = 0; //start all threads now to gain them to their freedom

    for (int i = 0; i < THREAD_COUNT; i++){ //now join them with main program
        pthread_join(threads[i], NULL);
    }
    printf("Lists are empty now\n\nProgram is closing...\n");

    //and free all lists
    free_list(favlist);
    free_list(prlist_first);
    free_list(prlist_second);
}