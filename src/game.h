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
#include "event.h"
#include "timer.h"

class Game {
protected:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* screenSurface = NULL;
    Event* event = NULL;
    Timer* fpsTimer = new Timer();
    bool running;
public:
    Game() {
        running = true;
        event = new Event(this);
        fpsTimer->start();
    }

    virtual void update(double delta);

    virtual void render();

    virtual void setup();

    bool initialize();

    virtual void run();

    virtual void exit();

    SDL_Window getWindow();

    SDL_Renderer getRenderer();

    SDL_Surface getSurface();
};

#endif //__fisk3d__game__
