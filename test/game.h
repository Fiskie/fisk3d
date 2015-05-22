//
//  game.h
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#ifndef __test__game__
#define __test__game__

#include <SDL2/sdl.h>
#include "event.h"

class Event;

class Game {
protected:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *screenSurface = NULL;
    Event *event = NULL;
    bool running;
    
public:
    Game();
	void update(double delta);
    void render();
    bool initialize();
    void processInput();
    void onKeyPress(SDL_Keycode key);
    void run();
    void exit();
    
    SDL_Window getWindow();
    SDL_Renderer getRenderer();
    SDL_Surface getSurface();
};

#endif /* defined(__test__game__) */
