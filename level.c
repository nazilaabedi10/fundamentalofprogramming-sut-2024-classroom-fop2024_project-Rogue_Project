#include "rogue.h"

//typedef struct Level{
    //char**tiles;
    //int level;
    //int numberOfRooms;
    //struct Room**rooms;
    //struct Monster**monsters;
    //int numberOfMonsters;
//}Level;,

Level*createLevel(int level){
    Level*newLevel;
    newLevel=malloc(sizeof(Level));

    newLevel->level=level;
    newLevel->numberOfRooms=7;
    newLevel->rooms=roomsSetUp();
    newLevel->tiles=saveLevelPositions();

    newLevel->user = playerSetUp();

    addMonsters(newLevel);

    return newLevel;
}

Room ** roomsSetUp(){
    Room ** rooms;
    rooms = malloc(sizeof(Room*)*14);
    if(rooms==NULL){
        return NULL;
    }

    rooms[0]=createRoom(3, 10, 4, 6);
    drawRoom(rooms[0]);


    rooms[1]=createRoom(10, 2, 5, 6);
    drawRoom(rooms[1]);


    rooms[2]=createRoom(15, 10, 6, 6);
    drawRoom(rooms[2]);


    rooms[3]=createRoom(25, 2, 6, 6);
    drawRoom(rooms[3]);


    rooms[4]=createRoom(40, 2, 7, 6);
    drawRoom(rooms[4]);


    rooms[5]=createRoom(30, 10, 6, 4);
    drawRoom(rooms[5]);


    rooms[6]=createRoom(43, 10, 6, 6);
    drawRoom(rooms[6]);
    
    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
    connectDoors(rooms[1]->doors[2], rooms[0]->doors[0]);

    return rooms;
}

char ** saveLevelPositions(){
    int x,y;
    char ** Positions;
    Positions= malloc(sizeof(char*)*25);

    for(y=0; y<25; y++){
        Positions[y]=malloc(sizeof(char)*100);
        for(x=0; x<100; x++){
            Positions[y][x]=mvinch(y,x);
        }
    }
    return Positions;
}