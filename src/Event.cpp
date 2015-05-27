//
//  event.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include <iostream>
#include "Event.h"

using namespace std;

Event::Event(Game *game) {
    this->game = game;
}

void Event::onKeyDown(SDL_Keycode key) {
    printf("Key ID: %d\n", key);

    Player *player = game->getPlayer();

    switch (key) {
        case SDLK_w:
        case SDLK_UP:
            player->addMovement(MOVEMENT_FORWARD);
            break;
        case SDLK_DOWN:
        case SDLK_s:
            player->addMovement(MOVEMENT_BACKWARD);
            break;
        case SDLK_LEFT:
        case SDLK_a:
            player->addMovement(MOVEMENT_LEFT);
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            player->addMovement(MOVEMENT_RIGHT);
            break;
    }

    cout << player->posAsString() << "\n";
}

void Event::onKeyUp(SDL_Keycode key) {
    printf("Key ID: %d\n", key);

    Player *player = game->getPlayer();

    switch (key) {
        case SDLK_w:
        case SDLK_UP:
            player->removeMovement(MOVEMENT_FORWARD);
            break;
        case SDLK_DOWN:
        case SDLK_s:
            player->removeMovement(MOVEMENT_BACKWARD);
            break;
        case SDLK_LEFT:
        case SDLK_a:
            player->removeMovement(MOVEMENT_LEFT);
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            player->removeMovement(MOVEMENT_RIGHT);
            break;
    }

    cout << player->posAsString() << "\n";
}

void Event::onMouseMotion(SDL_MouseMotionEvent motion) {
    Player *player = ((Game *) game)->getPlayer();

    player->rot.x += motion.xrel;
    player->rot.y += motion.yrel;

    cout << player->posAsString() << "\n";
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
                onKeyDown(e.key.keysym.sym);
                break;
            case SDL_KEYUP:
                onKeyUp(e.key.keysym.sym);
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