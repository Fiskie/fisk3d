//
//  game.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include <SDL2_ttf/SDL_ttf.h>
#include "Game.h"

Game::Game() {
    running = true;
    event = new Event(this);
    fpsTimer->start();
}

bool Game::initialize() {
    // todo exceptions, what the fuck is this

    if (TTF_Init() < 0) {
        printf("SDL_TTF could not initialize! Error: %s\n", TTF_GetError());
        return false;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create window
    window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, 0, 0);

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    setup();

    return true;
}

void Game::run() {
    if (!initialize())
        return;

    double delta = 0;
    long prev = SDL_GetTicks();

    const int FRAME_RATE = 60;
    const int TICK_TIME = 1 / FRAME_RATE;

    int frames = 0;

    while (running) {

        long now = SDL_GetTicks();
        long updateLength = now - prev;

        delta += ((double) updateLength / 1000);

        prev = now;

        if (delta >= TICK_TIME) {
            event->handle();
            update(delta);
            render();
            delta = 0;
            frames++;

            // printf("Frames: %d, Now: %d, Update length: %d\n", frames, now, updateLength);
            // printf("FPS: %f\n", (now / (double) frames));
        } else {
            SDL_Delay(TICK_TIME - delta);
        }
    }
}

void Game::exit() {
    running = false;

    // Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

SDL_Window *Game::getWindow() {
    return window;
}

SDL_Renderer *Game::getRenderer() {
    return renderer;
}

void Game::setMap(Map *map) {
    this->map = map;
}

Map *Game::getMap() {
    return map;
}