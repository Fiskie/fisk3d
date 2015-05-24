//
//  game.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "Game.h"

Game::Game() {
    running = true;
    event = new Event(this);
    fpsTimer->start();
}

bool Game::initialize() {
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
    
    // Get window surface
    screenSurface = SDL_GetWindowSurface( window );
    
    // Fill
    // SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    setup();

    return true;
}

void Game::run() {
    if (!initialize())
        return;

    double delta = 0;
    long prev = SDL_GetTicks();

    int frames = 0;

    while (running) {

        long now = SDL_GetTicks();
        long updateLength = now - prev;

        delta += ((double) updateLength / 1000);

        prev = now;

        if (delta >= 0.05) { // Game logic updates 1/20th a second.
            update(delta);
            render();
            delta = 0;
            frames++;

            // printf("Frames: %d, Now: %d, Update length: %d\n", frames, now, updateLength);
            printf("FPS: %f\n", (now / (double) frames));
        } else {
            SDL_Delay(0.05 - delta);
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