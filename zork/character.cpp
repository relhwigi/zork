#include "character.h"
#include <iostream>
#include "eventmanager.h"

using namespace std;

Character::Character(string name)
{
    this->name  = name; // We need to use "this->" to differentiate between the "name" argument and the "name" from the class.
    health      = 100;
    stamina     = 100;
    currentRoom = nullptr;
}

Character::~Character(){
    delete currentRoom;
    vector<item>().swap(itemsTaken);
}

string Character::getName()
{
    return name;
}

int Character::getHealth()
{
    return health;
}

int Character::getStamina()
{
    return stamina;
}

Room *Character::getCurrentRoom()
{
    return currentRoom;
}

void Character::setName(string name)
{
    this->name = name;
}

void Character::setHealth(int health)
{
    if (health <= 0) {
        health = 0;
        EventManager::getInstance().trigger("characterDeath", this);
    }

    this->health = health;
}

void Character::setStamina(int stamina)
{
    if (stamina <= 0) {
        stamina = 0;
        EventManager::getInstance().trigger("characterDeath", this);
    }

    this->stamina = stamina;
}

const void Character::setCurrentRoom(Room *next)
{
    currentRoom = next;
}

void Character::itemTaken(item *t){
    itemsTaken.push_back(*t);
}

bool Character::hasTakenItem(string t){
    if(itemsTaken.size() == 0) return false;
    for(int i = 0; i < itemsTaken.size(); i++){
        if(itemsTaken[i].getDescription() == t)
            return true;
    }
    return false;
}

void Character::clearItems(){
    itemsTaken.clear();
}

/****************** 5. Binary operator overloading******************/
ostream &operator<<(ostream &output, const Character &character){
    output << character.name << "-> HP: " << character.health << ". ST: " << character.stamina << ".\n";
    return output;
}
