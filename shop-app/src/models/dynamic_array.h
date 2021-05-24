//Arif Burak Demiray - 250201022
//This code compiled with C99

#ifndef DYNAMIC_ARRAY_H //include guard
#define DYNAMIC_ARRAY_H

typedef struct Array
{
    int size; //size of the array
    char* values; // values of the array
}Array;

int set(Array* array,Array* element); //changes values if element not greater than 50, 
                                    //if set successfully returns 1 else 0
Array initalize(); //initializes array from start to 5 bytes

int match(Array *array, char* value); //looks for values match with the array, 
                                    //if matches returns 1 else 0
int size(char* values); //returns the size of values

void toLowerCase(char* input); //converts string to lower case

char* split(char* sentence, char delimeter); //splits sentence by delimeter into 2 
                                            //and returns first element
void delete(Array* array); //deletes array

Array array(char* array); //makes an array struct from given char array

void copy(char list[],char* ptr); //copies given ptr char list to char list

int to_int(char* input); //converts a char array to integer

#endif /* DYNAMIC_ARRAY_H */

