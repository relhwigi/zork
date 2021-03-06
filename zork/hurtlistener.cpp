#include "hurtlistener.h"
#include "game.h"
#include <iostream>

HurtListener::HurtListener(Game *game)
{
    this->game = game;
}

void HurtListener::run(void *)
{
    game->getPlayer().setHealth(game->getPlayer().getHealth()-20);
    cout << "\nYou have been hurt. As a result your health has been affected.\n";
    
}
