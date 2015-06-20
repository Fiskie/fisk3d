//
//  game.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include <SDL2_ttf/SDL_ttf.h>
#include "Game.h"
#include "FatalGameException.h"
#include "Cameras/TopDownCamera.h"

Game::Game() {
    running = true;
}

void Game::initialize() {
    if (TTF_Init() < 0) {
        char err[] = "SDL_TTF could not initialize! Error: ";
        strcat(err, TTF_GetError());
        throw new FatalGameException(err);
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        char err[] = "SDL could not initialize! Error: ";
        strcat(err, SDL_GetError());
        throw new FatalGameException(err);
    }

    // Create window
    window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == NULL) {
        char err[] = "Window could not be created! Error: ";
        strcat(err, SDL_GetError());
        throw new FatalGameException(err);
    }

    renderer = SDL_CreateRenderer(window, 0, 0);

    if (renderer == NULL) {
        char err[] = "Renderer could not be created! Error: ";
        strcat(err, SDL_GetError());
        throw new FatalGameException(err);
    }

    setup();
}

void Game::run() {
    try {
        initialize();

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

                if (!running)
                    break;

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
    } catch (FatalGameException *ex) {
        printf("%s\n", ex->what());
    }

    onExit();
}

void Game::stop() {
    running = false;
}

void Game::onExit() {
    // Destroy window
    SDL_DestroyWindow(window);

    // Deallocate
    window = NULL;
    renderer = NULL;
    player = NULL;
    fpsTimer = NULL;

    // Quit SDL subsystems
    SDL_Quit();
    TTF_Quit();
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

void Game::render() {
    camera->render();
}

void Game::update(double delta) {
    player->move();
}

void Game::setup() {
    fpsTimer->start();
    event = new Event(this);
    camera = new TopDownCamera(this);
    player = new Player(this);

    player->vol.x = 10;
    player->vol.y = 80;
    player->vol.z = 10;

    player->loc.x = 300;
    player->loc.z = 300;
}

Player *Game::getPlayer() {
    return player;
}

Game::~Game() {
    this->onExit();
}
