#include "rogue.h"

int addMonsters(Level*level){
    int x;
    level->monsters=malloc(sizeof(Monster*)*6);
    level->numberOfMonsters=0;
    for(x=0; x<level->numberOfRooms; x++){
        if((rand()%2)==0){
            level->monsters[level->numberOfMonsters]=selectMonsters(level->level);
            setStartingPosition(level->monsters[level->numberOfMonsters], level->rooms[x]);
            level->numberOfMonsters++;
        }
    }
}
Monster*selectMonster(int level){
    int monster;
    switch(level){
        case 1:
        case 2:
        case 3:
            monster=(rand()%2)+1;
            break;
        case 4:
        case 5:
            monster=(rand()%2) +2;
            break;
        case 6:
            monster=3;
            break;
    }
/*
1 Spider
    symbol:X
    level:1-3
    health:2
    attack:1
    speed:1
    defence:1
    pathfinding:1 (random)

2 Goblin
    symbol:G
    level:1-5
    health:5
    attack:3
    speed:1
    defence:1
    pathfinding:2 (seeking)

3 Troll
    symbol:T
    level:4-6
    health:15
    attack:5
    speed:1
    defence:1
    pathfinding:1 (random)

*/

    switch (monster){
    case 1:/*spider*/
        return createMonster('X', 2, 1, 1, 1, 1);
    
    case 2: /*goblin*/
        return createMonster('G', 5, 3, 1, 1, 2);

    case 3: /*troll*/
        return createMonster('T', 15, 5, 1, 1, 1);
    }
}
Monster*creatMonster(char symbol, int health, int attack, int speed, int defence, int pathfinding){
    Monster*newMonster;
    newMonster=malloc(sizeof(Monster));

    newMonster->symbol=symbol;
    newMonster->health=health;
    newMonster->attack=attack;
    newMonster->speed=speed;
    newMonster->defence=defence;
    newMonster->pathfinding=pathfinding;
    newMonster->alive=1;

    sprintf(newMonster->string, "%c", symbol);

    newMonster->position=malloc(sizeof(Position));

    return newMonster;
}
int killMonster(Monster*monster){
    mvprintw(monster->position->y, monster->position->x, ".");
    monster->alive=0;

    return 1;
}

int setStartingPosition(Monster*monster, Room*room){
    monster->position->x=(rand()%(room->width -2))+room->position.x + 1;
    monster->position->y=(rand()%(room->height -2))+room->position.y + 1;

}
int moveMonsters(Level*level){
    int x;
    for(x=0; x<level->numberOfMonsters; x++){

        if(level->monsters[x]->alive==0)
            continue;
            
        mvprintw(level->monsters[x]->position->y, level->monsters[x]->position->x, ".");

        /*random*/
        if(level->monsters[x]->pathfinding==1){
            pathfindingRandom(level->monsters[x]->position);
            
        }else{
            pathfindingSeek(level->monsters[x]->position, level->user->position);
        }
        mvprintw(level->monsters[x]->position->y, level->monsters[x]->position->x, level->monsters[x]->string );
    }
}
int pathfindingSeek(Position*start, Position*destination){
    //step left
        if((abs((start->x- 1) - destination->x)<abs(start->x - destination->x))&& (mvinch(start->y, start->x - 1)=='.')){
            start->x=start->x-1;

        //step right
        }else if((abs((start->x + 1) - destination->x)<abs(start->x - destination->x))&& (mvinch(start->y, start->x + 1)=='.')){
            start->x=start->x+1;

        //step down
        }else if((abs((start->y + 1) - destination->y)<abs(start->y - destination->y))&& (mvinch(start->y + 1, start->x)=='.')){
           start->y=start->y+1;

        //step up
        }else if((abs((start->y - 1) - destination->y)<abs(start->y - destination->y))&& (mvinch(start->y - 1, start->x)=='.')){
            start->y=start->y - 1;
        }else{
            /*do nothing*/
        }
        return 1;
}
Monster*getMonsterAt(Position*position, Monster**monsters){
    int x;
    for(x=0; x<12; x++){
        if((position->y==monsters[x]->position->y)&&(position->x==monsters[x]->position->x))
            return monsters[x];
    }
    return NULL;
}
/**/