//Arif Burak Demiray 
//This code is compiled with C99
#include "string.h"

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
    for (int i = 0; i < len; i++)
    {
        list[i] = ptr[i]; //and copy it
    }
}

//This function initializes a string struct
string init_str()
{
    string str = {" ", 0}; //create empty
    return str;            //then return
}

string String(char *values, int listNum)
{                                         //listnum is the number of products1 or products2
    string str = init_str();              //initialize string struct
    copy(str.word, values, size(values)); //copy given char values to struct's char array
    str.list = listNum;
    return str;
}

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