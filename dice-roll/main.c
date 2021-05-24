// This code compiled with C99
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "printer.h"
#include <string.h>

void program();
void game(Player p1, Player p2, Player p3, Player p4);

void main(){
    program();
}



void game(Player p1, Player p2, Player p3, Player p4){
    char ch;
    int i=1;
    while(ch != 'n'){
    printf("Roll the dice (y/n)?: ");
    scanf("\n%c",&ch);
    if(ch!='y' & ch!='n'){
        printf("Please enter a valid option\n\n");
        }
    else if(ch=='y'){
        if(i%10==1)
            printf("%dst round:\n\n",i);
        else if(i%10==2)
            printf("%dnd round:\n\n",i);
        else if(i%10==3)
            printf("%drd round:\n\n",i);
        else
            printf("%dth round:\n\n",i);
        if(roll_print_results(&p1))
            break;
        else if(roll_print_results(&p2))
            break;
        else if(roll_print_results(&p3))
            break;
        else if(roll_print_results(&p4))
            break;
        print_table(p1,p2,p3,p4,i);
        i++;
        }
    }
    print_table(p1,p2,p3,p4,-1);
    printf("See you again %s\n\n",p4.name);
}


//gcc -std=c99 -o outputfile sourcefile.c
void program(){
    srand(time(0));
    char username[50];
    char start[50];
    printf("Please enter username: ");
    scanf("\n%s",username);
    printf("User registered as '%s' \n",username);
    while(1){
    printf("Type 'start' to begin the game or 'quit' to quit from the game: ");
    scanf("\n%s",&start);
    if(strcmp(start,"start")==0){
        Player user,p1,p2,p3;
        user.name=username;
        p1.point=0;
        p2.point=0;
        p3.point=0;
        user.point=0;
        p1.name="Player1";
        p2.name="Player2";
        p3.name="Player3";
        game(p1,p2,p3,user);
        return;}
    else if(strcmp(start,"quit")==0)
        {
            printf("See you again %s\n\n",username);
            return;
        }
    else{
        printf("Please type correct!!\n\n");
    }
    }
}


