#include "takelistener.h"
#include "game.h"

TakeListener::TakeListener(Game *game)
{
    this->game = game;
}

void TakeListener::run(void *)
{
    if (game->is_over()) {
        return;
    }

    this->game->take();
}
