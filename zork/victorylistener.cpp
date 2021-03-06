#include "victorylistener.h"

#include<iostream>

#include "game.h"

VictoryListener::VictoryListener(Game *game)
{
    this->game = game;
}

void VictoryListener::run(void *)
{
    cout << endl;
    cout << "You have found the key to unlock the room" << endl;
    cout << "Victory!\n" << endl;
    game->setOver(true);
}

