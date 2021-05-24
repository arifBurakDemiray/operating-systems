//Arif Burak Demiray 
//This code compiled with GNU99

#ifndef DYNAMIC_ARRAY_H //include guard
#define DYNAMIC_ARRAY_H

typedef struct Array
{
    int size;     //size of the array
    char *values; // values of the array
} Array;

//changes arrays values by element values, like a copy function
void set(Array *array, Array *element);

//initializes array from start to 5 bytes
Array initalize();

//returns the size of values
int size(char *values);

//converts string to lower case
void toLowerCase(Array *input);

//splits sentence by delimeter into 2 and returns first element
int split(char *sentence, char *delimeter);

//deletes array
void delete (Array *array);

//makes an array struct from given char array
Array array(char *array);

//copies given ptr char list to char list
void copy(char list[], char *ptr,int len);

//converts a char array to integer
int to_int(char *input);

//frees a list of Array struct
void free_array(Array *array, int len);

#endif /* DYNAMIC_ARRAY_H */
