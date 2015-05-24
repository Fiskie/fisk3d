//
//  game.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Game::Game() {
    running = true;
    event = new Event(this);
    fpsTimer->start();
}

void Game::update(double delta) {
    // Logic here
}

void Game::render() {
    // Render code here
}

void Game::setup() {
    // Setup code here
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

    /*
    
    // Get window surface
    screenSurface = SDL_GetWindowSurface( window );
    
    // Fill
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF)); */

    setup();

    return true;
}

void Game::run() {
    if (!initialize())
        return;

    Timer timer;

    double frameRate = 10000;
    double previous = clock();
    double lag = 0.0;

    while (running) {
        double current = clock();
        double elapsed = current - previous;

        previous = current;
        lag += elapsed;

        while (lag >= frameRate) {
            event->handle();
            update(lag);
            lag -= frameRate;
            SDL_Delay(100);
        }

        render();
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