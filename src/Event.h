//
//  event.h
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#ifndef __fisk3d__events__
#define __fisk3d__events__

#include <stdio.h>
#include "Game.h"

class Game;

class Event {
private:
    Game *game;

public:
    Event(Game *game);

    void handle();

    void onKeyPress(SDL_Keycode key);

    void onMouseMotion(SDL_MouseMotionEvent motion);

    void onMousePress(SDL_MouseButtonEvent event);
};

#endif //__fisk3d__events__
