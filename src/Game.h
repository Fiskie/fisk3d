//
//  game.h
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#pragma once

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "Timer.h"
#include "Map.h"
#include "World/Player.h"
#include <list>
#include "FatalGameException.h"

class Event;

class Map;

class Camera;

class Player;

class Wall;

class Game {
private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    Event *event = NULL;
    Timer fpsTimer;
    bool running;
    Map *map;
    Player *player;
    // list<Camera> *cameras; todo
    Camera *camera;
public:
    int frames;

    ~Game();

    Game();

    void update(double delta);

    void render();

    void setup();

    void initialize();

    virtual void run();

    virtual void onExit();

    Map *getMap();

    void setMap(Map *map);

    SDL_Window *getWindow();

    SDL_Renderer *getRenderer();

    Player *getPlayer();

    void stop();

    void setResolution(int x, int y);

    int originX;
    int originZ;
    int resX;
    int resY;

    void changeCamera();

    float avgFPS;
};

#include "Event.h"
#include "Cameras/Camera.h"
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
                              SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_GRABBED);

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
    Timer *capTimer = new Timer();

    try {
        initialize();

        double delta = 0;
        long prev = SDL_GetTicks();

        const double UPDATE_RATE = 60;
        const double TICK_TIME = 1000 / UPDATE_RATE;

        frames = 0;

        fpsTimer.start();

        while (running) {
            capTimer->start();

            avgFPS = frames / ( fpsTimer.getTicks() / 1000.f );

            if (avgFPS > 2000000)
                avgFPS = 0;

            long now = SDL_GetTicks();
            long updateLength = now - prev;

            delta += ((double) updateLength / 1000);

            prev = now;

            event->handle();

            if (!running)
                break;

            update(delta);
            render();
            delta = 0;
            frames++;

            // If frame finished early
            int frameTicks = capTimer->getTicks();

            if (frameTicks < TICK_TIME)
            {
                //Wait remaining time
                SDL_Delay((Uint32) TICK_TIME - frameTicks);
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
    SDL_RenderClear(renderer);

    camera->render();

    // need to rewrite this to use the stack
    SDL_Rect minimapRect = SDL_Rect{25,25,200,200};
    TopDownCamera *top = new TopDownCamera(this, minimapRect);
    top->zoom = 0.3;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderFillRect(renderer, &minimapRect);
    top->render();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    SDL_RenderDrawRect(renderer, &minimapRect);
    delete top;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderPresent(renderer);
}

void Game::update(double delta) {
    player->move();
}

void Game::setup() {
    fpsTimer.start();
    event = new Event(this);
    camera = new FirstPersonCamera(this);
    player = new Player(this);

    player->vol.x = 10;
    player->vol.y = 80;
    player->vol.z = 10;

    player->loc.x = -50;
    player->loc.y = 0;
    player->loc.z = -50;

    SDL_ShowCursor(0);
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
        delete camera;
        camera = new TopDownCamera(this);
    } else {
        delete camera;
        camera = new FirstPersonCamera(this);
    }
}
