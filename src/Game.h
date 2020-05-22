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
#include "World/state.cpp"
#include "World/Player.h"
#include <list>
#include "FatalGameException.h"

class Event;

class Map;

class Player;

class Wall;

class Game
{
private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    Event *event = NULL;
    Timer fpsTimer;
    bool running;
    
    TTF_Font *font;

public:
    State *state;
    Map *map;
    Player *player;

    int frames;

    ~Game()
    {
        this->onExit();
    }

    Game()
    {
        running = true;
    }

    void update(double delta)
    {
        player->move();
    }

    void render();

    void setup();

    void initialize();

    virtual void run();

    virtual void onExit();

    SDL_Window *getWindow()
    {
        return window;
    }

    SDL_Renderer *getRenderer()
    {
        return renderer;
    }

    void stop()
    {
        running = false;
    }

    SDL_Rect defaultViewport()
    {
        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h);
        return SDL_Rect{0, 0, w, h};
    }

    void setResolution(int x, int y)
    {
        this->resX = x;
        this->resY = y;
        this->originX = x / 2;
        this->originZ = y / 2;
    }

    int originX;
    int originZ;
    int resX;
    int resY;

    void changeCamera()
    {
        // whatever
    }

    float avgFPS;
};

#include "Event.h"
#include "Cameras/TopDownCamera.h"
#include "Cameras/PerspectiveCamera.h"

void Game::initialize()
{
    if (TTF_Init() < 0)
    {
        char err[] = "SDL_TTF could not initialize! Error: ";
        strcat(err, TTF_GetError());
        throw FatalGameException(err);
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        char err[] = "SDL could not initialize! Error: ";
        strcat(err, SDL_GetError());
        throw FatalGameException(err);
    }

    // Create window
    window = SDL_CreateWindow("fisk3d", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_GRABBED);

    if (window == NULL)
    {
        char err[] = "Window could not be created! Error: ";
        strcat(err, SDL_GetError());
        throw FatalGameException(err);
    }

    renderer = SDL_CreateRenderer(window, 0, 0);

    if (renderer == NULL)
    {
        char err[] = "Renderer could not be created! Error: ";
        strcat(err, SDL_GetError());
        throw FatalGameException(err);
    }

    font = TTF_OpenFont("OpenSans-Regular.ttf", 11);

    if (font == NULL)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        throw FatalGameException("Could not load required font.");
    }

    setup();
}

void Game::run()
{
    Timer capTimer;

    try
    {
        initialize();

        double delta = 0;
        long prev = SDL_GetTicks();

        const double UPDATE_RATE = 60;
        const double TICK_TIME = 1000 / UPDATE_RATE;

        frames = 0;

        fpsTimer.start();

        while (running)
        {
            capTimer.start();

            avgFPS = frames / (fpsTimer.getTicks() / 1000.f);

            if (avgFPS > 2000000)
                avgFPS = 0;

            long now = SDL_GetTicks();
            long updateLength = now - prev;

            delta += ((double)updateLength / 1000);

            prev = now;

            event->handle();

            if (!running)
                break;

            update(delta);
            render();
            delta = 0;
            frames++;

            // If frame finished early
            int frameTicks = capTimer.getTicks();

            if (frameTicks < TICK_TIME)
            {
                //Wait remaining time
                SDL_Delay((Uint32)TICK_TIME - frameTicks);
            }
        }
    }
    catch (FatalGameException *ex)
    {
        printf("%s\n", ex->what());
    }

    onExit();
}

void Game::onExit()
{
    // Destroy window
    SDL_DestroyWindow(window);

    // Deallocate
    window = NULL;
    renderer = NULL;

    delete player;
    delete event;

    // Quit SDL subsystems
    SDL_Quit();
    TTF_Quit();
}

void Game::render()
{
    SDL_RenderClear(renderer);

    PerspectiveCamera fps;
    fps.game = this;
    fps.viewport = defaultViewport();
    fps.font = font;
    fps.pos = player->pos;
    fps.rot = player->rot;
    fps.render();

    auto def = defaultViewport();
    SDL_Rect minimapRect = SDL_Rect{def.w - 225, 25, 200, 200};
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderFillRect(renderer, &minimapRect);

    TopDownCamera top;
    top.game = this;
    top.viewport = minimapRect;
    top.font = font;
    top.zoom = 0.3;
    top.render();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    SDL_RenderDrawRect(renderer, &minimapRect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderPresent(renderer);
}

void Game::setup()
{
    fpsTimer.start();
    event = new Event(this);
    player = new Player(this);

    player->vol.x = 10;
    player->vol.y = 80;
    player->vol.z = 10;

    player->pos.x = -50;
    player->pos.y = 0;
    player->pos.z = -50;

    SDL_ShowCursor(0);
}