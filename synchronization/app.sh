#!/bin/bash

printf "\nHello, Welcome to my program\nPress 1 to compile or recompile and run\nPress 2 to not compile and run\nPress 3 to remove executed file\nPress 4 to use valgrind\nChoice: "
read -e input
printf "\n~~~~~~~~~~~~~~~~~~~\n"

FILE=app.out

if [ $input == "1" ]; 
    then
    gcc --std=c99 -o app.out main.c linked_list.c product.c operations.c string.c -lpthread -w
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
            if [ $input == "4" ]
            then
                if [ ! -f "$FILE" ]
                then
                    printf "\nThere is no such file named $FILE\n"
                else
                    valgrind --leak-check=full --track-origins=yes ./app.out
                    printf "\nValgrind executed succesfully\n"
                fi
            else
                printf "You pressed wrong button please try again.\n"
            fi
        fi
    fi
fi
printf "\n~~~~~~~~~~~~~~~~~~~\n\n"