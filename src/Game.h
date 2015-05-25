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
#include "Map.h"

class Event;
class Map;

class Game {
protected:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    Event *event = NULL;
    Timer *fpsTimer = new Timer();
    bool running;
    Map *map;
public:
    Game();

    virtual void update(double delta) = 0;

    virtual void render() = 0;

    virtual void setup() = 0;

    void initialize();

    virtual void run();

    virtual void exit();

    Map *getMap();

    void setMap(Map *map);

    SDL_Window *getWindow();

    SDL_Renderer *getRenderer();
};

#endif //__fisk3d__game__
