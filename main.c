#include "rogue.h"

 int main(){
    Player*user;
    int ch;

    screenSetUp();

    mapSetUp();

    user = playerSetUp();
    //main game loop
    while((ch = getch())!='q')
    {
        handleInput(ch, user);
    }

    getch();

    endwin();

    return 0;
}

int screenSetUp(){
    initscr();
    printw("HellloWorld!");
    noecho();
    refresh();

    srand(time(NULL));

    return 1;
}