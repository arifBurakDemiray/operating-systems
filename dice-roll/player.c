#include "player.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
//#include"player1.h"

//returns the position of different roll and one of the equal rolls
//otherwise returns -1 for not found
int* look_for_difference(int* rolls){ 
    int* pos = malloc(sizeof(int)*2);
    if(rolls[0]==rolls[1]){
        pos[0] = 2;
        pos[1] = 1; 
        return pos;}
    else if(rolls[0]==rolls[2]){
        pos[0] = 1;
        pos[1] = 2;
        return pos;}
    else if(rolls[1]==rolls[2]){
        pos[0] = 0;
        pos[1] = 1;
        return pos;}
    else{
        pos[0] = -1;
        pos[1] = -1;
        return pos;
    }
}
//returns 1 if found ,else 0 for not found
int find_number(int* rolls, int number){
    for(int i =0;i<3;i++){
        if(rolls[i]==number)
            return 1;
    }
    return 0;

}

int gained_point(int* rolls){
    if(rolls[0]==1 & rolls[1]==1 & rolls[2]==1){
        return -10;
    }
    else if(rolls[0]==6 & rolls[1]==6 & rolls[2]==6){
        return  10;
    }
    else if(rolls[0]==rolls[1] & rolls[0]==rolls[2]){
        return  5;
    }
    else {
        int* positions = look_for_difference(rolls);
        if(positions[0]==-1){
            if(find_number(rolls,1) & find_number(rolls,2) & find_number(rolls,3))
                return  -3;
            else if(find_number(rolls,4) & find_number(rolls,5) & find_number(rolls,6))
                return  3;
            else
                return 0;
        }
        else if(rolls[positions[1]]<4)
            return  -rolls[positions[0]];
        else
            return  rolls[positions[0]];
    }
}

int* roll_dices(void){
    int roll1 = (rand() % 6)+1;
    int roll2 = (rand() % 6)+1;
    int roll3 = (rand() % 6)+1;
    int* rolls = malloc(sizeof(int)*3);
    rolls[0] = roll1;
    rolls[1] = roll2;
    rolls[2] = roll3;
    return rolls;
}