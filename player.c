#include "rogue.h"

Player*playerSetUp(){
Player*newPlayer;
newPlayer = malloc(sizeof(Player));
newPlayer->position = malloc(sizeof(Position));

newPlayer->health=20;
newPlayer->attack=1;
newPlayer->gold=0;
newPlayer->exp=0;
newPlayer->maxHealth=20;

return newPlayer;
}

int placePlayer(Room**rooms, Player*user){
    user->position->x=rooms[3]->position.x+1;
    user->position->y=rooms[3]->position.y+1;

    mvprintw(user->position->y, user->position->x, "@");
    move(user->position->y, user->position->x);
}
int handleInput(int input, Player*user){

    Position*newPosition;
    newPosition=malloc(sizeof(Position));
    switch(input){
        //move up
        case 'j':
        case 'J':
        newPosition->y=user->position.y-1;
        newPosition->x=user->position.x;
            break;

        //move down
        case 'k':
        case 'K':
            newPosition->y=user->position->y+1;
            newPosition->x=user->position->x;
            break; 

        //move left
        case 'h':
        case 'H':
            newPosition->y=user->position->y;
            newPosition->x=user->position->x-1;
            break;

        //move right
        case 'l':
        case 'L':
            newPosition->y=user->position->y;
            newPosition->x=user->position->x+1;
            break;

        //move northeast
        case 'u':
        case 'U':
            newPosition->y=user->position->y-1;
            newPosition->x=user->position->x+1;
            break;

        //move northwest
        case 'y':
        case 'Y':
            newPosition->x=user->position->y-1;
            newPosition->x=user->position->x-1;
            break;

        //move southeast
        case 'n':
        case 'N':
            newPosition->y=user->position->y+1;
            newPosition->x=user->position->x+1;
            break;

        //move southwest
        case 'b':
        case 'B':
            newPosition->y=user->position->y+1;
            newPosition->x=user->position->x-1;

        default:
            break;
        
    }
    checkPosition(newY, newX, user);
}
//check what is at next position
int checkPosition(int newY, int newX, Player*user){
    int space;
    switch(mvinch(newY,newX)){
        case '.':
        case '#':
        case '+':
            playerMove(newY,newX, user);
            break;
        default:
            move(user->position.y, user->position.x);
            break;
    }
}

int playerMove(int y, int x, Player*user){
    mvprintw(user->position.y, user->position.x, ".");
    user->position.y=y;
    user->position.x=x;
    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x);
}