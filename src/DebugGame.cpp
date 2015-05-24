//
//  debuggame.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "DebugGame.h"

void DebugGame::drawWall(Wall wall) {
    SDL_SetRenderDrawColor(renderer, 66, 66, 255, 1);
    SDL_RenderDrawLine(renderer, (int) wall.loc.x, (int) wall.loc.z, (int) (wall.loc.x + wall.vol.x), (int) wall.loc.z);
    SDL_RenderDrawLine(renderer, (int) wall.loc.x, (int) wall.loc.z, (int) wall.loc.x, (int) (wall.loc.z + wall.vol.z));
    SDL_RenderDrawLine(renderer, (int) (wall.loc.x + wall.vol.x), (int) wall.loc.z, (int) wall.loc.x, (int) (wall.loc.z + wall.vol.z));
    SDL_RenderDrawLine(renderer, (int) wall.loc.x, (int)  (wall.loc.z + wall.vol.z), (int) (wall.loc.x + wall.vol.x), (int) wall.loc.z);
}

void DebugGame::drawPlayer(Player player) {
    SDL_SetRenderDrawColor(renderer, 255, 66, 255, 1);
    SDL_RenderDrawLine(renderer, (int) player.loc.x, (int) player.loc.z, (int) (player.loc.x + player.vol.x), (int) player.loc.z);
    SDL_RenderDrawLine(renderer, (int) player.loc.x, (int) player.loc.z, (int) player.loc.x, (int) (player.loc.z + player.vol.z));
    SDL_RenderDrawLine(renderer, (int) (player.loc.x + player.vol.x), (int) player.loc.z, (int) player.loc.x, (int) (player.loc.z + player.vol.z));
    SDL_RenderDrawLine(renderer, (int) player.loc.x, (int) (player.loc.z + player.vol.z), (int) (player.loc.x + player.vol.x), (int) player.loc.z);
}

void DebugGame::drawDebugInfo() {

}

void DebugGame::render() {
    // printf("Rendering...\n");
    // drawPlayer(player);
    // drawWall(wall1);
    // drawWall(wall2);
    // drawWall(wall3);
    // drawWall(wall4);
    // drawDebugInfo();
}

void DebugGame::update(double delta) {
    printf("Updating... %f\n", delta);
}

void DebugGame::setup() {
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