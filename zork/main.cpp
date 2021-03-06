#include<cstdlib> // EXIT_SUCCESS macro.

#include "eventmanager.h"
#include "game.h"

#include "inputlistener.h"

int main()
{
    Game game;
    EventManager::getInstance().listen("input", new InputListener(&game));
    EventManager::getInstance().event_loop();
    return EXIT_SUCCESS;
}
