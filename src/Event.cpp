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
    Player *player = game->getPlayer();

    switch (key) {
        case SDLK_w:
        case SDLK_UP:
            player->addMovement(ACTION_MOVE_FORWARD);
            break;
        case SDLK_LSHIFT:
            player->addMovement(ACTION_SPRINT);
            break;
        case SDLK_DOWN:
        case SDLK_s:
            player->addMovement(ACTION_MOVE_BACKWARD);
            break;
        case SDLK_LEFT:
        case SDLK_a:
            player->addMovement(ACTION_MOVE_LEFT);
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            player->addMovement(ACTION_MOVE_RIGHT);
            break;
        case SDLK_r:
            player->addMovement(ACTION_MOVE_UP);
            break;
        case SDLK_f:
            player->addMovement(ACTION_MOVE_DOWN);
            break;
        case SDLK_c:
            game->changeCamera();
    }
}

void Event::onKeyUp(SDL_Keycode key) {
    Player *player = game->getPlayer();

    switch (key) {
        case SDLK_w:
        case SDLK_UP:
            player->removeMovement(ACTION_MOVE_FORWARD);
            break;
        case SDLK_LSHIFT:
            player->removeMovement(ACTION_SPRINT);
            break;
        case SDLK_DOWN:
        case SDLK_s:
            player->removeMovement(ACTION_MOVE_BACKWARD);
            break;
        case SDLK_LEFT:
        case SDLK_a:
            player->removeMovement(ACTION_MOVE_LEFT);
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            player->removeMovement(ACTION_MOVE_RIGHT);
            break;
        case SDLK_r:
            player->removeMovement(ACTION_MOVE_UP);
            break;
        case SDLK_f:
            player->removeMovement(ACTION_MOVE_DOWN);
            break;
    }
}

void Event::onMouseMotion(SDL_MouseMotionEvent motion) {
    Player *player = game->getPlayer();

    player->rot.x -= (float) motion.xrel / 100;
    player->rot.y -= (float) motion.yrel / 100;
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
                game->stop();
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