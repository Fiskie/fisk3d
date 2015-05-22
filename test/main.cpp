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
#include "structs.h"
#include "worldobject.h"
#include "game.h"

/*
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

void drawWall(Wall wall) {
    SDL_SetRenderDrawColor(renderer, 66, 66, 255, 1);
	SDL_RenderDrawLine(renderer, wall.loc.x, wall.loc.z, wall.loc.x + wall.vol.x, wall.loc.z);
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
}*/

int main(int argc, const char * argv[]) {
    Game *game = new Game();
    
    if (game->initialize()) {
        //setup();
        game->run();
        game->exit();
        return 0;
    } else {
        game->exit();
        return 0;
    }
}