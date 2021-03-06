#include "room.h"

class Game;

Room::Room(string name) :
    name(name)
{
    exits["north"] = nullptr;
    exits["east"]  = nullptr;
    exits["south"] = nullptr;
    exits["west"]  = nullptr;
    room_item = nullptr;
    hasEnemy = false;
}

Room::~Room(){
    delete game;
    delete room_item;
}

string Room::getName()
{
    return name;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
    exits["north"] = north;
    exits["east"]  = east;
    exits["south"] = south;
    exits["west"]  = west;
}

Room *Room::getExit(string direction)
{
    return exits[direction];
}

item* Room::getRoomItem(){
    return room_item;
}

void Room::setRoomItem(item* i){
    room_item = i;
}

bool Room::hasItem(){
    if(room_item == nullptr) return false;
    return true;
}

vector<string> Room::possibleDirections(){
    vector<string> directions;
    
    if(exits["north"]!=nullptr){
        directions.push_back("north");
    }
    if(exits["east"]!=nullptr){
        directions.push_back("east");
    }
    if(exits["west"]!=nullptr){
        directions.push_back("west");
    }
    if(exits["south"]!=nullptr){
        directions.push_back("south");
    }
    
    return directions;
}

void Room::setHasEnemy(bool b){
    hasEnemy = b;
}

bool Room::getHasEnemy(){
    return hasEnemy;
}
/****************** 6. Friends******************/
string Room::getDescription(Game* game){
    if(game->player.getCurrentRoom() == this && game->stationaryEnemy.getCurrentRoom() == this && game->roamingEnemy.getCurrentRoom() == this) return "!![" + name + "]!!";
    if((game->player.getCurrentRoom() == this && game->stationaryEnemy.getCurrentRoom() == this) || (game->player.getCurrentRoom() == this && game->roamingEnemy.getCurrentRoom() == this)) return " ![" + name + "]! ";
    if(game->stationaryEnemy.getCurrentRoom() == this && game->roamingEnemy.getCurrentRoom() == this) return " !!"+name+"!! ";
    if(game->player.getCurrentRoom() == this) return "  ["+name+"]  ";
    if(game->stationaryEnemy.getCurrentRoom() == this || game->roamingEnemy.getCurrentRoom() == this) return "  !"+name+"!  ";
    return "   "+name+"   ";
}
