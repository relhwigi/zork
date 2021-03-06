#ifndef hurtlistener_h
#define hurtlistener_h

#include <stdio.h>
#include "eventlistener.h"

// HurtListener.h
class Game;

class HurtListener : public EventListener
{
public:
    HurtListener(Game *game);
    void run(void *args) override;
private:
   Game *game;
};

#endif /* hurtlistener_h */
