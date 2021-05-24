//This code compiled with GNU99
//Arif Burak Demiray 

#ifndef OPERATIONS_H //include guard
#define OPERATIONS_H

#include "dynamic_array.h" //for array struct

//This function checks a char whether it is Lowercase Letter or not, if not lowercase letter returns 1 else 0
int isNotLetter(char value);

//this function returns 1 if key is in source, but matches only cases
//like absolute, abs -> this is not a match
//     ..abs, abs -> this is a match
//       abs, abs -> this is a match
//       ABS, abs -> this is a match
//       Abs, abs -> this is a match
int contains(Array source, Array key);

//this function reads all file
char *read_file(char *filename);

//this function prints random words and their counts
void print_random_words(Array *words, int counts[], int word_size, int random_count, int max_book);

#endif /* OPERATIONS_H */
