//This code compiled with GNU99
//Arif Burak Demiray

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include "operations.h"
#include "main_operations.h"

//You can change thread count see difference by threads
//You can change random count to print more words
//You can change max book to read more or less books
#define BILLION 1e9     //for time calculation
#define MAX_SIZE 3      //when reading from file, average word count
#define THREAD_COUNT 64 //thread count
#define MAX_BOOK 10     //book count
#define RANDOM_COUNT 5  //random word count that is going to be printed

int BOOK_ID = 0;                    //current book id
struct timespec timeStart, timeEnd; //time start and end
Array *fileWords = NULL;            //book
int BOOK_SIZE = 0;                  //book size
int WORD_SIZE = 0;                  //keywords size
Array *keys;                        //keywords
int *COUNTS;                        //key counts
int current = 0;                    //wait condition for threads
int endTime = 0;                    //time ender
//thread function
//This function breaks book into parts, every thread looks for different parts of the books
//And searches every keyword in that part
void *occurence(void *args)
{
    while (current != THREAD_COUNT - 1); //wait all threads to start at the same time
    if (current == THREAD_COUNT - 1)
    {                                              //if all threads initialized
        clock_gettime(CLOCK_REALTIME, &timeStart); //start clock time
    }
    int core = *((int *)args);                         //thread number
    int start = core * BOOK_SIZE / THREAD_COUNT;       //start bound
    int i = start;                                     //start index
    int bound = (core + 1) * BOOK_SIZE / THREAD_COUNT; //end index
    for (i; i < bound; i++)                            //for all words
    {
        for (int j = 0; j < WORD_SIZE; j++)
        {                                        //for all keywords
            if (contains(fileWords[i], keys[j])) //if key is matches with book's word
            {
                COUNTS[BOOK_ID + j * MAX_BOOK] += 1; //increase match count
                break;                               //break because we found a match for that word
            }
        }
    }
    endTime++;
    if (endTime == THREAD_COUNT)//if all threads finished
    {
        clock_gettime(CLOCK_REALTIME, &timeEnd); //end time
        endTime = 0; //end reset time for the next run
    }
    free(args); //free thread number
}

//this function reads a book and torn aparts it to its words
void read_book(int book) //book number
{
    char filename[25] = {};
    sprintf(filename, "book%d.txt", book); //prepare filename for given book
    char *file = read_file(filename);      //read book

    int len = size(file);       //calculate len of the book
    BOOK_SIZE = len / MAX_SIZE; //approxiamte word counts
    Array searchs[BOOK_SIZE];   //book's words

    int i = 0;
    char *word = strtok(file, "\r\n "); //split by tokens to take words
    while (word != NULL)                //while word null
    {
        searchs[i] = initalize();     //initialize word
        Array tempPtr = array(word);  //create a dynamic array for word
        set(&searchs[i], &tempPtr);   //set temp as book's word
        toLowerCase(&searchs[i]);     //lowercase readed word to compare it with others
        i++;                          //go to new one
        word = strtok(NULL, "\r\n "); //split again
    }
    BOOK_SIZE = i;       //new book size is readed words
    fileWords = searchs; //make global book new book
    free(file);          //free readed book
}

//this function navigates threads
void find_occurence()
{
    pthread_t threads[THREAD_COUNT]; //create thread array
    int *count;                      //count for a word coming from all threads //get start time
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        int *number = malloc(sizeof(int));
        *number = i;
        current = i;                                          //prepare number to send to thread function
        pthread_create(&threads[i], NULL, occurence, number); //spawn thread
    }
    for (int j = 0; j < THREAD_COUNT; j++)
    {
        pthread_join(threads[j], NULL); //gather threads
    }
}

void start()
{
    srand(time(0));                          //for random
    char *fileName = "englishstopwords.txt"; //keywords
    char *file = read_file(fileName);        //read keywords
    int lenKeywords = size(file);            //take size of the keywords
    char tokens[4] = "\r\n";                 //split them
    WORD_SIZE = lenKeywords / MAX_SIZE;      //average words

    Array words[WORD_SIZE];            //keywords
    char *word = strtok(file, tokens); //split
    int i = 0;
    while (word != NULL)
    {
        words[i] = initalize(); //initialize it
        Array tempPtr = array(word);
        set(&words[i], &tempPtr); //set it
        i++;
        word = strtok(NULL, tokens); //continue to split
    }
    WORD_SIZE = i;                                 //make global word size counted words
    free(file);                                    //free keywords
    int counts[WORD_SIZE * MAX_BOOK];              //take a space for counts
    for (int k = 0; k < WORD_SIZE * MAX_BOOK; k++) //initialize counts matrix
    {
        counts[k] = 0;
    }
    COUNTS = counts;                                //make global counts, initialized counts
    keys = words;                                   //make global keys, read keys
    double totalTime = 0;                           //total time for all books and threads
    printf("\nfrequency calculation started...\n"); //start operations
    for (int i = 0; i < MAX_BOOK; i++)              //for in all books
    {
        BOOK_ID = i;      //set current book id
        read_book(i + 1); //read book
        find_occurence(); //start search operation for current book
        double time = (timeEnd.tv_sec - timeStart.tv_sec) + (timeEnd.tv_nsec - timeStart.tv_nsec) / BILLION;
        totalTime += time;                //calculate passed time
        free_array(fileWords, BOOK_SIZE); //free readed book
    }
    printf("frequency calculation ended...\n\n\n");
    print_random_words(keys, COUNTS, WORD_SIZE, RANDOM_COUNT, MAX_BOOK);                         //print random words
    printf("\n\nTotal execution time for %d threads: %lf seconds\n\n", THREAD_COUNT, totalTime); //print total tim1e

    free_array(keys, WORD_SIZE); //free keywords
}
