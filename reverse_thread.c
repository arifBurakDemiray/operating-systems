//This code compiled with GNU99
//Arif Burak Demiray 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define MAX 100

int THREAD_COUNT = 0;

typedef struct string
{
    char original[MAX];
    char reverse[MAX];
}string;


int size(char *values)
{
    int len = 0; //size
    char last;    //current char value
    while (1)
    {
        last = values[len]; //take current char
        if (last != '\0')    //if char not equal empty
            len++;          //increase
        else                 //otherwise means char array finished
            break;
    }
    return len; //return size
}

void copy(char list[], char *ptr)
{
    int sizeList = size(ptr); //calculates size of char array
    for (int i = 0; i < sizeList; i++)
    {
        list[i] = ptr[i]; //and copy it
    }
}

void *reverse_str(void *args)
{
    string* word = (string *)args;                      
    int originalSize = size(word->original);
    int j=0;
    for (int i=0; i <originalSize; i++) 
    {
        word->reverse[originalSize-i-1]=word->original[i];
        j++;
    }
}



void main(int argc, char *argv[] )
{
        
    THREAD_COUNT = argc-1;
    if(argc < 2){  
      printf("No argument passed through command line.\n");  
    }  
    else{ 
        pthread_t threads[THREAD_COUNT];     
        string words[THREAD_COUNT];      
        for (int i = 0; i < THREAD_COUNT; i++)
        {
            string* word = malloc(sizeof(string));
            copy(word->original,argv[i+1]);     
            words[i] = *word;                                  
            pthread_create(&threads[i], NULL, reverse_str, &words[i]); 
            printf("Created new thread with Id %d for %s\n",threads[i],words[i].original);
        }
        for (int j = 0; j < THREAD_COUNT; j++)
        {
            pthread_join(threads[j],NULL); 
            printf("\nThread Id %lu\nOriginal String: %s\nReversed String: %s\n",threads[j],words[j].original,words[j].reverse);
        }
    }
}


