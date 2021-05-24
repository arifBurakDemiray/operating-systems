#include "printer.h"
#include <stdio.h>

void sort(Player *pls);

int roll_print_results(Player * user){
    int* rolls = roll_dices();
    int gained = gained_point(rolls);
    user->point += gained;
    printf("%s rolled %d-%d-%d\n\n",user->name,rolls[0],rolls[1],rolls[2]);
    if(gained < 0)
        printf("%s lost %d points\n\n",user->name,gained);
    else
        printf("%s gained %d points\n\n",user->name,gained);
    if(user->point >= 20){
        printf("%s reached 20 points\n\n",user->name);
        printf("Congratulations, %s has won the game.\n\n",user->name);
        return 1;
    }
    else
        return 0;
}

void print_table(Player p1, Player p2, Player p3, Player p4, int round){
    printf("\n\n");
    if(round==-1)
        printf("Final Results Table\n\n");
    else if(round%10==1)
        printf("Points table after %dst round:\n\n",round);
    else if(round%10==2)
        printf("Points table after %dnd round:\n\n",round);
    else if(round%10==3)
        printf("Points table after %drd round:\n\n",round);
    else
        printf("Points table after %dth round:\n\n",round);
    Player pls[4] = {p1,p2,p3,p4};
    sort(pls);
    for(int i=3;i>=0;i--){
        printf("%d-%s %d points\n\n",(4-i),pls[i].name,pls[i].point);
    }
}

void sort(Player *pls){
    int i, j, min; 
    for (i = 0; i < 4; i++) 
    { 
        min = i; 
        for (j = i+1; j < 4; j++) 
          if (pls[j].point < pls[min].point) 
            min = j; 
        Player *temp1 = &pls[min];
        Player *temp2 = &pls[i];  
        Player temp = *temp1;
        *temp1 = *temp2;
        *temp2 = temp;
    } 
}