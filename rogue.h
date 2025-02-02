#ifndef ROGUE_H
#define ROGUE_H

#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<time.h>

/******Struct Definitions******/

typedef struct Levek{
    char**tiles;
    int level;
    int numberOfRooms;
    struct Room**rooms;
    struct Monsters;
    struct Player*user;
}Level;

typedef struct Position{
    int x;
    int y;
    //tile_type tile:
}Position;


typedef struct Room
{
    Position position;
    int height;
    int width;
    struct Door ** doors;
    int numberOfDoors;
    //Monster**monsters
    //Item**items;
}Room;


typedef struct Door
{
    Position*position;
    int connected;

}Door;


typedef struct Player{
    Position*position;
    int health;
    int attack;
    int gold;
    int maxHealth;
    int exp;
    //Room*room;
}Player;

typedef struct Monster{
    char string[2];
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    int pathfinding;
    int alive;
    Position*position;

}Monster;

/********Global Variable********/
int MAX_HEIGHT;
int MAX_WIDTH;

/*screen functions*/
int screenSetUp();
int printGameHub(Level*level);

/*level/map functions*/
Level* creatLevel();
Room ** mapSetUp();
char**saveLevelPositions();
void connectDoors(Level*level);

/*player functions*/
Player*playerSetUp();
Position*handleInput(int input, Player*user);
int checkPosition(Position*newPosition, Level*level);
int playerMove(Position*newPosition, Player*user, char**level);
int placePlayer(Room**rooms, Player*user);

//room functions 
Room*createRoom(int grid, int numberOfDoors);
int drawRoom(Room*room);

/*monster functions*/
int addMonster(Level*level);
Monster*selectMonster(int level);
Monster*creatMonster(char symbol, int health, int attack, int speed, int defence, int pathfinding);
int setStartingPosition(Monster*monster, Room*room);
int moveMonsters(Level*level);
int pathfindingSeek(Position*start, Position*destination);
int pathfindingRandom(Position*Position);
Monster*getMonsterAt(Position*position, Monster**monsters);
int killMonster(Monster*monster)


#endif