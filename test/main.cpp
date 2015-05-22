//
//  main.cpp
//  test
//
//  Created by Fiskie on 21/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <SDL2/sdl.h>
#include <SDL2_ttf/sdl_ttf.h>
#include "timer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
//const int FRAMES_PER_SECOND = 60;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The renderer
SDL_Renderer *renderer = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// Event handler
SDL_Event e;

// The font that's going to be used
TTF_Font *font = NULL;

// The color of the font
SDL_Color textColor = { 255, 255, 255 };

// Main running flag
bool running = true;

struct Pos {
    double x = 0;
    double y = 0;
    double z = 0;
};

struct Player {
    Pos loc;
    Pos rot;
    Pos vol;
};

struct Wall {
    Pos loc;
    Pos rot;
    Pos vol;
};

Player player;
Wall wall1;
Wall wall2;
Wall wall3;
Wall wall4;

void setup() {
    player.vol.x = 20;
    player.vol.y = 80;
    player.vol.z = 20;
    
    wall1.loc.x = 100;
    wall2.loc.z = 100;
    wall3.loc.x = -100;
    wall4.loc.z = -100;
    
    wall1.vol.x = 100;
    wall2.vol.x = 100;
    wall3.vol.x = 100;
    wall4.vol.x = 100;
    
    wall1.vol.z = 100;
    wall2.vol.z = 100;
    wall3.vol.z = 100;
    wall4.vol.z = 100;
    
    wall1.vol.y = 100;
    wall2.vol.y = -100;
    wall3.vol.y = 100;
    wall4.vol.y = -100;
}

bool init() {
    // Initialize SDL
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    renderer = SDL_CreateRenderer(gWindow, 0, 0);
    
    // Get window surface
  //  gScreenSurface = SDL_GetWindowSurface( gWindow );
    
    // Fill
//    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF));
    
    return true;
}

void onKeyPress(SDL_Keycode key) {
    switch (e.key.keysym.sym) {
        case SDLK_w:
            player.loc.x += 1;
            break;
        case SDLK_s:
            player.loc.x -= 1;
            break;
        case SDLK_a:
            player.loc.z = 1;
            break;
        case SDLK_d:
            player.loc.z -= 1;
            break;
    }
}

void processInput() {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                // Key press code here
                onKeyPress(e.key.keysym.sym);
                break;
        }
    }
}

void drawWall(Wall wall) {
    SDL_SetRenderDrawColor(renderer, 66, 66, 255, 1);
    printf("Line draw: %d", SDL_RenderDrawLine(renderer, wall.loc.x, wall.loc.z, wall.loc.x + wall.vol.x, wall.loc.z));
    SDL_RenderDrawLine(renderer, wall.loc.x, wall.loc.z, wall.loc.x, wall.loc.z + wall.vol.z);
    SDL_RenderDrawLine(renderer, wall.loc.x + wall.vol.x, wall.loc.z, wall.loc.x, wall.loc.z + wall.vol.z);
    SDL_RenderDrawLine(renderer, wall.loc.x, wall.loc.z + wall.vol.z, wall.loc.x + wall.vol.x, wall.loc.z);
    printf("Rendered wall (x: %f y: %f; w: %f h: %f", wall.loc.x, wall.loc.z, wall.vol.x, wall.vol.z);
}

void drawPlayer(Player player) {
    SDL_SetRenderDrawColor(renderer, 255, 66, 255, 1);
    SDL_RenderDrawLine(renderer, player.loc.x, player.loc.z, player.loc.x + player.vol.x, player.loc.z);
    SDL_RenderDrawLine(renderer, player.loc.x, player.loc.z, player.loc.x, player.loc.z + player.vol.z);
    SDL_RenderDrawLine(renderer, player.loc.x + player.vol.x, player.loc.z, player.loc.x, player.loc.z + player.vol.z);
    SDL_RenderDrawLine(renderer, player.loc.x, player.loc.z + player.vol.z, player.loc.x + player.vol.x, player.loc.z);
}

void drawDebugOverlay() {
    
}

void render() {
    drawPlayer(player);
    drawWall(wall1);
    drawWall(wall2);
    drawWall(wall3);
    drawWall(wall4);
    drawDebugOverlay();
}

void update() {
    // Logic
}

void close() {
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    
    // Quit SDL subsystems
    SDL_Quit();
}

void mainLoop() {
    Timer timer;
    
    double frameRate = 0.001;
    double previous = clock();
    double lag = 0.0;
    
    while (running) {
        double current = clock();
        double elapsed = current - previous;
        
        previous = current;
        lag += elapsed;
        
        processInput();
        
        while (lag >= frameRate)
        {
            update();
            lag -= frameRate;
        }
        
        render();
        SDL_Delay(1000);
    }
}

int main(int argc, const char * argv[]) {
    if (init()) {
        setup();
        mainLoop();
        close();
        return 0;
    } else {
        close();
        return 0;
    }
}