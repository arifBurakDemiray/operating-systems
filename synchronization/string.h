//Arif Burak Demiray 
//This code is compiled with C99


#ifndef STRING_H //include guard
#define STRING_H

typedef struct string //This struct is for sending inputs to first type thread 
{
    char word[30];
    int list;
}string;

//gets a size of char array
int size(char *values);  

//copies a char to char array with usage of size function 
void copy(char list[], char *ptr, int len);

//this function creates a new string for type 1 thread 
string String(char* values, int listNum);

//this function converts a char array to int, if cannot converted, returns -1 
int to_int(char* input); 

#endif /*STRING_H*/