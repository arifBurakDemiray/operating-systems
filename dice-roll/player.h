//Arif Burak Demiray 

#ifndef PLAYER_H //include guard
#define PLAYER_H

typedef struct Player
{
    int point;
    char* name;
}Player;

int gained_point(int* rolls);// points by roll variations
int* roll_dices(void); //returns random rolled 3 numbers as a list

#endif /* PLAYER_H */

