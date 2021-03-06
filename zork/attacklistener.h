#ifndef attacklistener_h
#define attacklistener_h

#include <stdio.h>

#include "eventlistener.h"


class Game;

// a listener for the attack command
class AttackListener : public EventListener
{
    public:
        AttackListener(Game *game);
        void run(void *args) override;
    
    private:
        Game *game;
};
#endif /* attacklistener_h */
