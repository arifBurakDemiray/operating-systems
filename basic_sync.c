//Arif Burak Demiray 
//A) after deposit 6000 sometimes 5000
//B) after withdraw always 5000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define THREAD_COUNT 2
int balance = 0;
int flag = 0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *deposit()
{
    for (int i=0;i<1;i++){
        pthread_mutex_lock(&mutex);
        balance+=1000;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
   
}

void *withdraw()
{
    for (int i=0;i<200;i++){
        pthread_mutex_lock(&mutex);
        if(balance < 1){
            pthread_cond_wait(&cond, &mutex);}
        balance-=5;
        pthread_mutex_unlock(&mutex);
    }
}


void main()
{

    pthread_t threads[THREAD_COUNT];             
    pthread_create(&threads[0], NULL, withdraw, NULL); //spawn thread
    pthread_create(&threads[1], NULL, deposit, NULL); //spawn thread
    pthread_join(threads[0], NULL); //gather threads
    printf("Deposit: %d\n",balance);
    pthread_join(threads[1], NULL); //gather threads
    printf("Withdraw: %d\n",balance);

}
