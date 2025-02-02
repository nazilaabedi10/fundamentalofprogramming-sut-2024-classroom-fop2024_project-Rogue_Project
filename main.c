#include "../include/rogue.h"
#include<mainMenu.h>

int gameLoop(){
        
    int ch;

    Position*newPosition;
    Level*level;

    level=creatLevel(1);
    printGameHub(level);

    //main game loop
    while((ch = getch())!='q')
    {
        printGameHub(level);
        newPosition=handleInput(ch, level->user);
        checkPosition(newPosition, level);
        moveMonstters(level);
        move(level->user->position->y, level->user->position->x);

        if(level->user->health<=0){
            return -1;
        }
    }
}

void menuLoop(){
    int choice;
    char* choices[]={"Start  Game", "End Game"};
    while(true){
        choice=mainMenu(2, choices);

        switch (choice)
        {
        case START_GAME:
            break;

        case QUIT_GAME:
            break;
            return;
        default:
            break;
        }
    }
}


 int main(){

    Position*newPosition;
    Level*level;

    screenSetUp();

    char* choices[]={"Start  Game", "End Game"};
    menuLoop();
    endwin();

    return 0;
}
