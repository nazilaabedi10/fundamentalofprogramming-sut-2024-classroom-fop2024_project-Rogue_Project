#include "rogue.h"

Room ** mapSetUp(){
    Room ** rooms;
    rooms = malloc(sizeof(Room*)*14);
    if(rooms==NULL){
        return NULL;
    }
    //mvprintw(10, 3, "------");
    //mvprintw(11, 3, "|....|");
    //mvprintw(12, 3, "|....|");
    //mvprintw(13, 3, "------");

    rooms[0]=createRoom(3, 10, 4, 6);
    drawRoom(rooms[0]);


    //mvprintw(2, 10, "------");
    //mvprintw(3, 10, "|....|");
    //mvprintw(4, 10, "|....|");
    //mvprintw(5, 10, "|....|");
    //mvprintw(6, 10, "------");

    rooms[1]=createRoom(10, 2, 5, 6);
    drawRoom(rooms[1]);



    //mvprintw(10, 15, "------");
    //mvprintw(11, 15, "|....|");
    //mvprintw(12, 15, "|....|");
    //mvprintw(13, 15, "|....|");
    //mvprintw(14, 15, "|....|");
    //mvprintw(15, 15, "------");

    rooms[2]=createRoom(15, 10, 6, 6);
    drawRoom(rooms[2]);

    
    //mvprintw(2, 25, "------");
    //mvprintw(3, 25, "|....|");
    //mvprintw(4, 25, "|....|");
    //mvprintw(5, 25, "|....|");
    //mvprintw(6, 25, "|....|");
    //mvprintw(7, 25, "------");

    rooms[3]=createRoom(25, 2, 6, 6);
    drawRoom(rooms[3]);

    
    //mvprintw(2, 40, "------");
    //mvprintw(3, 40, "|....|");
    //mvprintw(4, 40, "|....|");
    //mvprintw(5, 40, "|....|");
    //mvprintw(6, 40, "|....|");
    //mvprintw(7, 40, "|....|");
    //mvprintw(8, 40, "------");


    rooms[4]=createRoom(40, 2, 7, 6);
    drawRoom(rooms[4]);

    
    //mvprintw(10, 30, "----");
    //mvprintw(11, 30, "|..|");
    //mvprintw(12, 30, "|..|");
    //mvprintw(13, 30, "|..|");
    //mvprintw(14, 30, "|..|");
    //mvprintw(15, 30, "----");

    rooms[5]=createRoom(30, 10, 6, 4);
    drawRoom(rooms[5]);

    
    //mvprintw(10, 43, "------");
    //mvprintw(11, 43, "|....|");
    //mvprintw(12, 43, "|....|");
    //mvprintw(13, 43, "|....|");
    //mvprintw(14, 43, "|....|");
    //mvprintw(15, 43, "------");

    rooms[6]=createRoom(43, 10, 6, 6);
    drawRoom(rooms[6]);
    
    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
    connectDoors(rooms[1]->doors[2], rooms[0]->doors[0]);

    return rooms;


}
Room*createRoom(int x,int y,int height,int width){
    Room*newRoom;
    newRoom = malloc(sizeof(Room));
    newRoom->position.x=x;
    newRoom->position.y=y;
    newRoom->height=height;
    newRoom->width=width;

    srand(time(NULL));

    newRoom->doors = malloc(sizeof(Position*)*8);

    //top door
    newRoom->doors[0]=malloc(sizeof(Position));
    newRoom->doors[0]->x=rand() % (width-2) + newRoom->position.x + 1;
    newRoom->doors[0]->y=newRoom->position.y;

    //left door
    newRoom->doors[1]=malloc(sizeof(Position));
    newRoom->doors[1]->y=rand() % (height-2) + newRoom->position.y + 1;
    newRoom->doors[1]->x=newRoom->position.x;

    //bottom door
    newRoom->doors[2]=malloc(sizeof(Position));
    newRoom->doors[2]->x=rand() % (width-2) + newRoom->position.x + 1;
    newRoom->doors[2]->y=newRoom->position.y + newRoom->height - 1;

    //right door
    newRoom->doors[3]=malloc(sizeof(Position));
    newRoom->doors[3]->y=rand() % (height-2) + newRoom->position.y + 1;
    newRoom->doors[3]->x=newRoom->position.x + width - 1;


    return newRoom;
}

int drawRoom(Room*room){
    int x;
    int y;

    //draw top and buttom
    for (x = room->position.x; x < room->position.x + room->width; x++) {
        mvprintw(room->position.y, x, "-"); //top
        mvprintw(room->position.y + room->height-1, x, "-"); //bottom
    }
    //draw floors and side walls
    for (int y = room->position.y+1; y < room->position.y + room->height-1; y++) {
        // draw side walls
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width -1, "|");
        //draw floors
        for(x=room->position.x+1;x < room->position.x+room->width-1; x++){
            mvprintw(y, x, ".");
        }
        refresh();
    }
    //draw doors
    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");
    return 1;
}

int connectDoors(Position*doorOne, Position*doorTow){
    Position temp;
    Position previous;

    int count=0;

    temp.x=doorOne->x;
    temp.y=doorOne->y;

    previous=temp;

    while(1){
        //step left
        if((abs((temp.x - 1) - doorTow->x)<abs(temp.x - doorTow->x))&& (mvinch(temp.y, temp.x - 1)==' ')){
            previous.x=temp.x;
            temp.x=temp.x-1;

        //step right
        }else if((abs((temp.x + 1) - doorTow->x)<abs(temp.x - doorTow->x))&& (mvinch(temp.y, temp.x + 1)==' ')){
            previous.x=temp.x;
            temp.x=temp.x+1;

        //step down
        }else if((abs((temp.y + 1) - doorTow->y)<abs(temp.y - doorTow->y))&& (mvinch(temp.y + 1, temp.x)==' ')){
           previous.y=temp.y;
           temp.y=temp.y+1;

        //step up
        }else if((abs((temp.y - 1) - doorTow->y)<abs(temp.y - doorTow->y))&& (mvinch(temp.y - 1, temp.x)==' ')){
            previous.y=temp.y;
            temp.y=temp.y - 1;

        }else{
            if(count==0){
                temp=previous;
                count++;
                continue;
            }else{
                return 0;
            }
        }
        mvprintw(temp.y, temp.x, "#");
        getch();
    }
    return 1;
}