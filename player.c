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

}
Position* handleInput(int input, Player*user){

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
    checkPosition(Position*newPosition, Level*level);
}
//check what is at next position
int checkPosition(Position*newPosition, Level*level){
    Player*user;
    user=level->user;
    int space;
    switch(mvinch(newPosition->y,newPosition->x)){
        case '.':
        case '#':
        case '+':
            playerMove(newPosition, user, level->tiles);
            break;
        case 'X':
        case 'G':
        case 'T':
            combat(user,getMonsterAt(newPosition,level->monsters),1);
        default:
            break;
    }
}

int playerMove(Position*newPosition, Player*user, char**level){
    char buffer[8];

    sprintf(buffer, "%c", level[user->position->y][user->position->x]);

    user->position->y=newPosition->y;
    user->position->x=newPosition->x;

    mvprintw(user->position->y, user->position->x, "@");
    move(user->position->y, user->position->x);
}