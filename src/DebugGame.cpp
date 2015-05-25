//
//  debuggame.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "DebugGame.h"

void DebugGame::drawBrush(Brush *brush) {
    SDL_SetRenderDrawColor(renderer, 66, 255, 255, 1);
    SDL_RenderDrawLine(renderer, (int) brush->loc.x, (int) brush->loc.z, (int) (brush->loc.x + brush->vol.x),
                       (int) brush->loc.z);
    SDL_RenderDrawLine(renderer, (int) brush->loc.x, (int) brush->loc.z, (int) brush->loc.x,
                       (int) (brush->loc.z + brush->vol.z));
    SDL_RenderDrawLine(renderer, (int) (brush->loc.x + brush->vol.x), (int) brush->loc.z,
                       (int) (brush->loc.x + brush->vol.x),
                       (int) (brush->loc.z + brush->vol.z));
    SDL_RenderDrawLine(renderer, (int) brush->loc.x, (int) (brush->loc.z + brush->vol.z),
                       (int) (brush->loc.x + brush->vol.x),
                       (int) (brush->loc.z + brush->vol.z));
}

void DebugGame::drawPlayer(Player *player) {
    SDL_SetRenderDrawColor(renderer, 255, 66, 255, 1);
    SDL_RenderDrawLine(renderer, (int) player->loc.x, (int) player->loc.z, (int) (player->loc.x + player->vol.x),
                       (int) player->loc.z);
    SDL_RenderDrawLine(renderer, (int) player->loc.x, (int) player->loc.z, (int) player->loc.x,
                       (int) (player->loc.z + player->vol.z));
    SDL_RenderDrawLine(renderer, (int) (player->loc.x + player->vol.x), (int) player->loc.z,
                       (int) (player->loc.x + player->vol.x),
                       (int) (player->loc.z + player->vol.z));
    SDL_RenderDrawLine(renderer, (int) player->loc.x, (int) (player->loc.z + player->vol.z),
                       (int) (player->loc.x + player->vol.x), (int) (player->loc.z + player->vol.z));
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