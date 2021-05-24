#!/bin/bash

printf "\nHello, Welcome to my program\nPress 1 to compile or recompile and run\nPress 2 to not compile and run\nPress 3 to remove executed file\nChoice: "
read -e input
printf "\n~~~~~~~~~~~~~~~~~~~\n"

FILE=src/program/program.out

if [ $input == "1" ]; 
    then
    gcc -std=c99 -o src/program/program.out src/program/program.c src/controllers/operations.c src/models/product.c src/models/dynamic_array.c 
    printf "\nProgram starting...\n\n"
    ./src/program/program.out
else
    if [ $input == "2" ] 
    then
        if [ ! -f "$FILE" ]
        then
            printf "\nThere is no such file named $FILE\n"
        else
            printf "\nProgram starting...\n\n"
            ./src/program/program.out
        fi
    else
        if [ $input == "3" ]
        then
            if [ ! -f "$FILE" ]
            then
                printf "\nThere is no such file named $FILE\n"
            else
                rm src/program/program.out
                printf "\nProgram deleted succesfully\n"
            fi
        else
        printf "You pressed wrong button please try again.\n"
        fi
    fi
fi
printf "\n~~~~~~~~~~~~~~~~~~~\n\n"