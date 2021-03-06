#include "enemy.h"

Enemy::Enemy(string name, bool roamer) : Character(name){
    this->roamer = roamer;
}

bool Enemy::getRoamer(){
    return roamer;
}

