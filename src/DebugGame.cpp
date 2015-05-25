//
//  debuggame.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "DebugGame.h"

void DebugGame::drawBrush(Brush *brush) {
    double lX = brush->loc.x;
    double lY = brush->loc.y;
    double lZ = brush->loc.z;
    double vX = brush->vol.x;
    double vY = brush->vol.y;
    double vZ = brush->vol.z;

    double pX = player->loc.x;
    double pY = player->loc.y;
    double pZ = player->loc.z;

    SDL_SetRenderDrawColor(renderer, 66, 255, 255, 1);
    SDL_RenderDrawLine(renderer, (int) lX, (int) lZ, (int) (lX + vX), (int) lZ);
    SDL_RenderDrawLine(renderer, (int) lX, (int) lZ, (int) lX, (int) (lZ + vZ));
    SDL_RenderDrawLine(renderer, (int) (lX + vX), (int) lZ, (int) (lX + vX), (int) (lZ + vZ));
    SDL_RenderDrawLine(renderer, (int) lX, (int) (lZ + vZ), (int) (lX + vX), (int) (lZ + vZ));
}

void DebugGame::drawPlayer(Player *player) {
    SDL_SetRenderDrawColor(renderer, 255, 66, 255, 1);

    double relX = player->loc.x - player->vol.x / 2;
    double relY = player->loc.y - player->vol.y / 2;
    double relZ = player->loc.z - player->vol.z / 2;

    SDL_RenderDrawLine(renderer, (int) relX, (int) relZ, (int) (relX + player->vol.x),
                       (int) relZ);
    SDL_RenderDrawLine(renderer, (int) relX, (int) relZ, (int) relX,
                       (int) (relZ + player->vol.z));
    SDL_RenderDrawLine(renderer, (int) (relX + player->vol.x), (int) relZ,
                       (int) (relX + player->vol.x),
                       (int) (relZ + player->vol.z));
    SDL_RenderDrawLine(renderer, (int) relX, (int) (relZ + player->vol.z),
                       (int) (relX + player->vol.x), (int) (relZ + player->vol.z));

    // Render rotation

    SDL_SetRenderDrawColor(renderer, 255, 255, 66, 1);

    SDL_RenderDrawLine(renderer, (int) player->loc.x, (int) player->loc.z, (int) player->loc.x - 10, (int) player->loc.z);
}

void DebugGame::drawDebugInfo() {

}

void DebugGame::render() {
    // printf("Rendering...\n");

    SDL_RenderClear(renderer);

    list<Brush> *objs = map.getBrushes();

    list<Brush>::iterator i;

    for (i = objs->begin(); i != objs->end(); ++i) {
        drawBrush(&(*i));
    }

    drawPlayer(player);

    drawDebugInfo();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);

    // SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(renderer);
}

void DebugGame::update(double delta) {
    // printf("Updating... %f\n", delta);
}

void DebugGame::setup() {
    player = new Player();

    player->vol.x = 10;
    player->vol.y = 80;
    player->vol.z = 10;

    player->loc.x = 300;
    player->loc.z = 300;
}

Player *DebugGame::getPlayer() {
    return player;
}