#include "rogue.h"

Player*playerSetUp(){
Player*newPlayer;
newPlayer = malloc(sizeof(Player));

newPlayer->position.x=14;
newPlayer->position.y=14;
newPlayer->health=20;

mvprintw(newPlayer->position.y, newPlayer->position.x, "@");
move(newPlayer->position.y, newPlayer->position.x);
refresh();

return newPlayer;

}
int handleInput(int input, Player*user){

    int newY;
    int newX;
    switch(input){
        //move up
        case 'j':
        case 'J':
        newY=user->position.y-1;
        newX=user->position.x;
            break;

        //move down
        case 'k':
        case 'K':
            newY=user->position.y+1;
            newX=user->position.x;
            break; 

        //move left
        case 'h':
        case 'H':
            newY=user->position.y;
            newX=user->position.x-1;
            break;

        //move right
        case 'l':
        case 'L':
            newY=user->position.y;
            newX=user->position.x+1;
            break;

        //move northeast
        case 'u':
        case 'U':
            newY=user->position.y-1;
            newX=user->position.x+1;
            break;

        //move northwest
        case 'y':
        case 'Y':
            newY=user->position.y-1;
            newX=user->position.x-1;
            break;

        //move southeast
        case 'n':
        case 'N':
            newY=user->position.y+1;
            newX=user->position.x+1;
            break;

        //move southwest
        case 'b':
        case 'B':
            newY=user->position.y+1;
            newX=user->position.x-1;

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