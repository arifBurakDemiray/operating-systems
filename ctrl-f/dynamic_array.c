//Arif Burak Demiray 
//This code compiled with GNU99

#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>

//calculates size of a char array
int size(char *values)
{
    int size = 0; //size
    char last;    //current char value
    while (1)
    {
        last = values[size]; //take current char
        if (last != '\0')    //if char not equal empty
            size++;          //increase
        else                 //otherwise means char array finished
            break;
    }
    return size; //return size
}

//copies a given char array to char list
void copy(char list[], char *ptr, int len)
{
    //int sizeList = size(ptr); //calculates size of char array
    for (int i = 0; i < len; i++)
    {
        list[i] = ptr[i]; //and copy it
    }
}

//destructor for array struct
void delete (Array *array)
{
    free(array->values);  //free char values
    array->values = NULL; //make pointer null
}

//changes arrays values to element values if successful returns 1 else 0
void set(Array *array, Array *element)
{
    array->size = element->size;              //update size
    char *temp = malloc(array->size);         //take space for new values
    delete (array);                           //delete old values
    copy(temp, element->values, array->size); //and copy element to buffer
    array->values = temp;                     //than make values buffer
}

//initially create an array struct
Array initalize()
{
    Array dynamic;            //array
    char *values = malloc(5); //initially 5
    dynamic.values = values;  //make values values
    dynamic.size = 5;         //make size 5
    return dynamic;           //and return it
}

//this function creates a dynamic array from given char array
Array array(char *array)
{
    Array dynamic;               //array struct
    int sizeArray = size(array); //calculate size of the char array
                                 /*     if(sizeArray > 0 & array[sizeArray-1]=='\n')    //if there is newline at the end
        array[sizeArray-1]='\0';    //eliminate it */
    dynamic.values = array;      //make values array
    dynamic.size = sizeArray;    //update size
    return dynamic;              //return it
}

//this function lowers char arrays
void toLowerCase(Array *input)
{
    int max = input->size; //calculate size
    for (int i = 0; i < max; i++)
    {
        if (input->values[i] >= 65 && input->values[i] <= 90)
        {                             //if values in range of A,B....Y,Z
            input->values[i] = input->values[i] + 32; //make it a,b..y,z
        }                             //because there is 32 difference from A to a,B to b,..Y to y,Z to z
    }
}

//this function splits a sentence into 2 by given delimeter
int split(char *sentence, char *delimeter)
{
    int max = size(sentence); //calculate size
    int delSize = size(delimeter);
    int wordSize = -1; //found delimeter location
    for (int i = 0; i < max; i++)
    {
        if (sentence[i] == delimeter[0])
        { //if delimeter location
            wordSize = i;
            for (int j = 0; j < delSize; j++)
            {
                if (sentence[i] == delimeter[j])
                {
                }
                else
                    return -1;
            }
            break; //break
        }
    }
    return wordSize;
}

//converts a char to integer, returns number if successful
//otherwise returns -1
int to_int(char *input)
{
    int len = size(input); //calculate size
    int isOkey = 0;        //if it is okey to convert
    for (int i = 0; i < len; i++)
    {
        if (input[i] >= 48 & input[i] <= 57)
        {             //if char values in range 0 to 9
            isOkey++; //increase isOkey
        }
        if (input[i] == '\n') //if there is newline at the end
            isOkey++;         //increase isOkey
    }
    if (isOkey == len)
    {                       //if isOkey equal to char len
        return atoi(input); //convert to integer
    }
    return -1; //otherwise return -1
}

//this function deletes all elements of an array by its len
void free_array(Array *array, int len)
{
    for (int i = 0; i < len; i++)//delete all elements
    {
        delete (&array[i]);
    }
    array = NULL;
}