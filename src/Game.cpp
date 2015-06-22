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
#include "Cameras/FirstPersonCamera.h"

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
    window = SDL_CreateWindow("fisk3d", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY,
                              SDL_WINDOW_SHOWN);

    // Disable the cursor...
    // SDL_ShowCursor(0);

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

        const double UPDATE_RATE = 60;
        const double RENDER_RATE = 60;
        const double TICK_TIME = 1 / UPDATE_RATE;

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
    fpsTimer = NULL;

    delete player;
    delete event;
    delete camera;

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
    camera = new FirstPersonCamera(this);
    player = new Player(this);

    player->vol.x = 10;
    player->vol.y = 80;
    player->vol.z = 10;

    player->loc.x = -50;
    player->loc.z = -50;
}

Player *Game::getPlayer() {
    return player;
}

Game::~Game() {
    this->onExit();
}

void Game::setResolution(int x, int y) {
    this->resX = x;
    this->resY = y;
    this->originX = x / 2;
    this->originZ = y / 2;
}

void Game::changeCamera() {
    if (FirstPersonCamera *p = dynamic_cast<FirstPersonCamera *>(camera)) {
        camera = new TopDownCamera(this);
    } else {
        camera = new FirstPersonCamera(this);
    }
}
