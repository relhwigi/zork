#ifndef GAME_H
#define GAME_H

#include<string>
#include<vector>

#include "character.h"
#include "room.h"
#include "item.h"
#include "enemy.h"

using namespace std;

class Room;

class Game
{
    
    /****************** 6. Friends******************/
    friend  class Room;
    
public:
    Game();
    ~Game();
    void reset(bool show_update = true);

    void map();
    void info();
    void go(string direction);
    void teleport();
    void update_screen();
    Character &getPlayer();
    void setOver(bool over);
    bool is_over();
    void setCurrentRoom(Room *next);
    void distribute_items();
    void lockRoom();
    void take();
    Room* getLockedRoom();
    void enemies();
    void roam();
    void attack();
    
   

private:
    Character      player;
    Enemy          stationaryEnemy;
    Enemy          roamingEnemy;
    vector<Room *> rooms;
    bool           gameOver;
    Room           *locked;
    bool           secondAttack; // tells player enemy is weak after first attack and to attack again to kill enemy. set to true when                                   enemy requires a second attack, set to false when player leaves room.
    int            keyIndex;
    item           *cursed;
    item           *key;
    item           *potion;
   
};
#endif // GAME_H
