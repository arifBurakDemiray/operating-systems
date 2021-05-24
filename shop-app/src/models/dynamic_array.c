//Arif Burak Demiray - 250201022
//This code compiled with C99

#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>

//calculates size of a char array
int size(char* values){
    int size = 0;   //size
    char last;      //current char value
    while(1){
        last = values[size];    //take current char
        if(last!='\0')      //if char not equal empty
            size++; //increase
        else    //otherwise means char array finished
            break;
    }
    return size;    //return size
}

//copies a given char array to char list
void copy(char list[],char* ptr){
    int sizeList = size(ptr);    //calculates size of char array
    for(int i=0;i<sizeList;i++){    
        list[i]=ptr[i]; //and copy it
    }
}

//destructor for array struct
void delete(Array* array){
    free(array->values);    //free char values
    array->values = NULL;  //make pointer null
}

//changes arrays values to element values if successful returns 1 else 0
int set(Array* array,Array* element){
    if(element->size/sizeof(char) > 50){ //if size greater than 50 return 0
        return 0;
    }
    int sizeArray = array->size;    //size of array
    int sizeElement = element->size;    //size of element
    while(!(sizeArray/sizeElement >= 1)){   //look for if we have enough space 
        sizeArray=sizeArray*2;}             //otherwise double size
    array->size=sizeArray;      //update size
    char* temp = malloc(sizeArray);     //take space for new values
    delete(array);      //delete old values
    copy(temp,element->values);     //and copy element to buffer
    array->values=temp;     //than make values buffer
    return 1;       //return 1
}

//initially create an array struct
Array initalize(){
    Array dynamic;      //array
    char* values = malloc(5);   //initially 5
    dynamic.values = values;    //make values values
    dynamic.size=5; //make size 5
    return dynamic; //and return it
}

//this function creates a dynamic array from given char array
Array array(char* array){
    Array dynamic;  //array struct
    int sizeArray = size(array);    //calculate size of the char array
    if(sizeArray > 0 & array[sizeArray-1]=='\n')    //if there is newline at the end
        array[sizeArray-1]='\0';    //eliminate it
    dynamic.values=array;   //make values array
    dynamic.size=sizeArray; //update size
    return dynamic; //return it
}

//this function lowers char arrays
void toLowerCase(char* input){
    int max = size(input);  //calculate size
    for(int i=0;i<max;i++){     
        if(input[i] >=65 && input[i]<=90){  //if values in range of A,B....Y,Z
            input[i] = input[i] + 32;       //make it a,b..y,z 
        }   //because there is 32 difference from A to a,B to b,..Y to y,Z to z
    }
}

//this function splits a sentence into 2 by given delimeter
char* split(char* sentence, char delimeter){
    int max = size(sentence);  //calculate size
    int wordSize = 0;   //found delimeter location
    for(int i = 0;i<max;i++){   
        if(sentence[i]==delimeter){ //if delimeter location
            break;  //break
        }else{
            wordSize++; //otherwise increase delimeter location
        }
    }
    char *result = malloc(wordSize); //take a space for first word
    for(int j = 0;j<wordSize;j++){  
        result[j]=sentence[j];  //copy sentence first word to result
    }
    return result;  //return it
}

//matches an array by given char array, if mathces 1 otherwise 0
int match(Array *array, char* value){
    int valueSize = size(value);    //calculate size
    int wordSize = size(array->values);     //calculate array size
    int min = (wordSize > valueSize) ? valueSize : wordSize; //find minimum one
    char input[wordSize];   //define buffers for search
    char prodValue[valueSize];  
    copy(input,array->values);  //copy values to buffers
    copy(prodValue,value);
    toLowerCase(input); //convert them to lower case
    toLowerCase(prodValue);
    int result = 0; //result
    for(int i=0;i<min;i++){ 
        if(input[i]==prodValue[i]){ //if char values are equal
            result++;  //increase result
        }
    }
    if(result==min){    //if result is equal to minimum one
        return 1;}  //return 1
    return 0;   //if not equal return 0
}

//converts a char to integer, returns number if successful
//otherwise returns -1
int to_int(char* input){    
    int len = size(input);  //calculate size
    int isOkey = 0;     //if it is okey to convert
    for(int i=0;i<len;i++){
        if(input[i]>=48 & input[i]<=57){    //if char values in range 0 to 9
            isOkey++;   //increase isOkey
        }
        if(input[i]=='\n') //if there is newline at the end 
            isOkey++;   //increase isOkey
    }
    if(isOkey==len){    //if isOkey equal to char len 
        return atoi(input); //convert to integer
    }
    return -1;  //otherwise return -1
}