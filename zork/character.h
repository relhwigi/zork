#ifndef CHARACTER_H
#define CHARACTER_H

#include<string>
#include<vector>
#include "item.h"

using namespace std;

// No need to include room since we're only working with pointers.
// This is how we tell the compiler "there will be a room eventually".
// This is called a "forward declaration".
class Room;

class Character
{
    
/****************** 5. Binary operator overloading******************/
/****************** 6. Friends******************/ // kinda but i'll do another example of the use of Friend, this 2 in 1 is kinda cheating i suppose. other example in game class
    friend ostream &operator<<(ostream &, const Character&);
    
    
public:
    Character(string name);
    ~Character();
    
    bool active;
    string getName();
    int    getHealth();
    int    getStamina();
    Room  *getCurrentRoom();
    bool hasTakenItem(string t);
    
    void setName(string name);
    void setHealth(int setHealth);
    void setStamina(int stamina);
    const void setCurrentRoom(Room *next);
    void itemTaken(item *t);
    void clearItems();

private:
    string name;
    int health;
    int stamina;
    Room *currentRoom;
    vector<item> itemsTaken;
};

#endif // CHARACTER_H
