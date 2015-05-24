//
//  game.h
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#ifndef __fisk3d__game__
#define __fisk3d__game__

#include <SDL2/sdl.h>
#include "Event.h"
#include "Timer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Event;

class Game {
protected:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* screenSurface = NULL;
    Event* event = NULL;
    Timer* fpsTimer = new Timer();
    bool running;
public:
    Game();

    virtual void update(double delta) = 0;

    virtual void render() = 0;

    virtual void setup() = 0;

    bool initialize();

    virtual void run();

    virtual void exit();

    SDL_Window getWindow();

    SDL_Renderer getRenderer();

    SDL_Surface getSurface();
};

#endif //__fisk3d__game__
