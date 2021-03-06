#ifndef enemy_h
#define enemy_h

#include <stdio.h>

#include "character.h"

class Enemy : public Character{
    
public:
    Enemy(string name, bool roamer);
    bool getRoamer();
private:
    bool roamer;
};

#endif /* enemy_h */
