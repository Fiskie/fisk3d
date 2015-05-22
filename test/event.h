//
//  event.h
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#ifndef __test__events__
#define __test__events__

#include <stdio.h>
#include <SDL2/sdl.h>
#include "game.h"

class Game;

class Event {
private:
    Game *game;
    
public:
    Event(Game *game);
    void handle();
    void onKeyPress(SDL_Keycode key);
};

#endif /* defined(__test__events__) */
