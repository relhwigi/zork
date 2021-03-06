#ifndef ROOM_H
#define ROOM_H

#include<map>
#include<string>
#include "item.h"
#include "character.h"
#include "game.h"
#include "enemy.h"

class Game;

using namespace std;

class Room
{
public:
    Room(string name);
    ~Room();
    string getName();
    void setExits(Room *north, Room *east, Room *south, Room *west);
    Room *getExit(string direction);
    item* getRoomItem();
    void setRoomItem(item* i);
    bool hasItem();
    vector<string> possibleDirections();
    void setHasEnemy(bool b);
    bool getHasEnemy();
    /****************** 6. Friends******************/
    string getDescription(Game *game);
    
private:
    string name;
    map<string, Room *> exits;
    item *room_item;
    bool hasEnemy;
    Game *game;
};

#endif // ROOM_H
