//
//  event.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "event.h"

Event::Event(Game* game) {
    this->game = game;
}

void Event::onKeyPress(SDL_Keycode key) {
    printf("Key ID: %d\n", key);
}

void Event::handle() {
    SDL_Event e;

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_QUIT:
                puts("Game exit called.\n");
                game->exit();
                break;
            case SDL_KEYDOWN:
                // Key press code here
                onKeyPress(e.key.keysym.sym);
                break;
        }
    }
}