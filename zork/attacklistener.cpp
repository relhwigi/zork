#include "attacklistener.h"
#include "game.h"

AttackListener::AttackListener(Game *game)
{
    this->game = game;
}

void AttackListener::run(void *)
{
    if (game->is_over()) {
        return;
    }

    this->game->attack();
}
