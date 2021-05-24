#!/bin/bash

printf "\nHello, Welcome to my program\nPress 1 to compile or recompile and run\nPress 2 to not compile and run\nPress 3 to remove executed file\nChoice: "
read -e input
printf "\n~~~~~~~~~~~~~~~~~~~\n"

FILE=app.out

if [ $input == "1" ]; 
    then
    gcc --std=gnu99 -o app.out app.c main_operations.c operations.c dynamic_array.c -lpthread -w
    printf "\nProgram starting...\n\n"
    ./app.out
else
    if [ $input == "2" ] 
    then
        if [ ! -f "$FILE" ]
        then
            printf "\nThere is no such file named $FILE\n"
        else
            printf "\nProgram starting...\n\n"
            ./app.out
        fi
    else
        if [ $input == "3" ]
        then
            if [ ! -f "$FILE" ]
            then
                printf "\nThere is no such file named $FILE\n"
            else
                rm app.out
                printf "\nProgram deleted succesfully\n"
            fi
        else
        printf "You pressed wrong button please try again.\n"
        fi
    fi
fi
printf "\n~~~~~~~~~~~~~~~~~~~\n\n"