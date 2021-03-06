#ifndef takelistener_h
#define takelistener_h

#include "eventlistener.h"
#include <stdio.h>

class Game;

// a listener for the take command
class TakeListener : public EventListener
{
    public:
        TakeListener(Game *game);
        void run(void *args) override;
    
    private:
        Game *game;
};

#endif /* takelistener_h */

