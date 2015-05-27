//
//  event.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include <iostream>
#include "Event.h"

void onMouseMotion(SDL_MouseMotionEvent event);

Event::Event(Game *game) {
    this->game = game;
}

void Event::onKeyPress(SDL_Keycode key) {
    printf("Key ID: %d\n", key);

    Player *player = ((Game *) game)->getPlayer();

    switch (key) {
        case SDLK_w:
        case SDLK_UP:
            player->loc.z += 10;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            player->loc.z -= 10;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            player->loc.x += 10;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            player->loc.x -= 10;
            break;
    }

    std::cout << player->posAsString() << "\n";
}

void Event::onMouseMotion(SDL_MouseMotionEvent motion) {
    Player *player = ((Game *) game)->getPlayer();

    player->rot.x += motion.xrel;
    player->rot.y += motion.yrel;

    std::cout << player->posAsString() << "\n";
}

void Event::onMousePress(SDL_MouseButtonEvent event) {
    //
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
                onMouseMotion(e.motion);
                break;
            case SDL_MOUSEBUTTONDOWN:
                onMousePress(e.button);
                break;
            default:
                break;
        }
    }
}