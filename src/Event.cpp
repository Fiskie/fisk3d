//
//  event.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "Event.h"
#include "DebugGame.h"

Event::Event(Game *game) {
    this->game = game;
}

void Event::onKeyPress(SDL_Keycode key) {
    printf("Key ID: %d\n", key);

    Player *player = ((DebugGame *) game)->getPlayer();

    switch (key) {
        case SDLK_w:
            player->loc.z--;
            break;
        case SDLK_s:
            player->loc.z++;
            break;
        case SDLK_a:
            player->loc.x--;
            break;
        case SDLK_d:
            player->loc.x++;
            break;
    }
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
            case SDL_MOUSEMOTION:
                printf("Mouse motion! %d %d\n", e.motion.xrel, e.motion.yrel);
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("Click at %d, %d", e.button.x, e.button.y);
                break;
            default:
                break;
        }
    }
}