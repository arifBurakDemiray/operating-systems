//This code compiled with GNU99
//Arif Burak Demiray

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

//function checks char is letter or not
int isNotLetter(char value)
{
    //Because I do lowercase at the start I only check for lowercase letters
    //if it is not in range of ([97,122]) it is not letter
    if (!(value >= 97 && value <= 122))
    {
        return 1;
    }
    return 0;
}

//This function like a modifed strcmp
int contains(Array source, Array key)
{
    int sourceSize = source.size; //took their size
    int keySize = key.size;
    if (keySize > sourceSize) //if key is greater than source return immediatily
        return 0;
    int result = 0; //find result

    int i = 0;
    for (i; i < sourceSize; i++)
    {
        //if rest of the key is not lesser or equal than source's rest return false
        if(sourceSize-i<keySize-result)
            return 0;
       //if value equal to result index of key char
        if (source.values[i] == key.values[result])
        {   //if result 0 but before letter of source is a letter, return zero like cases
            // cable, able   if a matches c is not matches with the word
            if(result==0 && !isNotLetter(source.values[i-1]))
                return 0;
            result++;
            //if all chars found and after char of source values is not a letter
            //like able! able 
            if(result==keySize){
                if(isNotLetter(source.values[i+1]))
                    return 1;
                else //if after is a letter return immediately
                    return 0;
            }
        }
        else if (result==0) //if result 0 means not found yet
        {
        }
        else{   //otherwise row is disrupted, so it is not wanted match return false
            //like label  lab
            return 0;
        }
    }
    return 0;
}

//this function reads all file as a char array
char *read_file(char *filename)
{
    char *allFile = NULL;
    int file_size = 0;
    FILE *file;
    file = fopen(filename, "r"); //read file
    if (file)                    //if file is opened succesfully
    {
        fseek(file, 0, SEEK_END);           //seek to the end of memory location
        file_size = ftell(file);            //calculate size
        rewind(file);                       //go back to beginning
        allFile = malloc(file_size);        //malloc space
        fread(allFile, 1, file_size, file); //and read all file
        fclose(file);                       //close file
    }
    return allFile; //and return
}

//this function prints random words for output and their counts
void print_random_words(Array *words, int counts[], int word_size, int random_count, int max_book)
{
    int random_index = 0;                  //random book index
    for (int i = 0; i < random_count; i++) //given random count
    {
        random_index = (rand() % word_size);                                              //rand by word size
        printf("frequency of the word “%s” in all books:\n", words[random_index].values); //print word
        for (int j = 0; j < max_book; j++)                                                //in book counts
        {
            //counts are holded like a matrix
            //       book1 book2 book3 ....... bookn
            // word1  15    20   56             n
            // word2  5
            // word3  45
            //     .
            //     .
            // wordm  m
            printf("%d", counts[random_index * max_book + j]); //print counts
            if (j != max_book - 1)                             //and if not end print -
                printf("-");
        }
        printf("\n"); //and print newline
    }
}