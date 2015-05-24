//
//  debuggame.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

void DebugGame::drawWall(Wall wall) {
    SDL_SetRenderDrawColor(renderer, 66, 66, 255, 1);
    SDL_RenderDrawLine(renderer, wall.loc.x, wall.loc.z, wall.loc.x + wall.vol.x, wall.loc.z);
    SDL_RenderDrawLine(renderer, wall.loc.x, wall.loc.z, wall.loc.x, wall.loc.z + wall.vol.z);
    SDL_RenderDrawLine(renderer, wall.loc.x + wall.vol.x, wall.loc.z, wall.loc.x, wall.loc.z + wall.vol.z);
    SDL_RenderDrawLine(renderer, wall.loc.x, wall.loc.z + wall.vol.z, wall.loc.x + wall.vol.x, wall.loc.z);
}

void DebugGame::drawPlayer(Player player) {
    SDL_SetRenderDrawColor(renderer, 255, 66, 255, 1);
    SDL_RenderDrawLine(renderer, player.loc.x, player.loc.z, player.loc.x + player.vol.x, player.loc.z);
    SDL_RenderDrawLine(renderer, player.loc.x, player.loc.z, player.loc.x, player.loc.z + player.vol.z);
    SDL_RenderDrawLine(renderer, player.loc.x + player.vol.x, player.loc.z, player.loc.x, player.loc.z + player.vol.z);
    SDL_RenderDrawLine(renderer, player.loc.x, player.loc.z + player.vol.z, player.loc.x + player.vol.x, player.loc.z);
}

void drawDebugOverlay() {

}

void DebugGame::render() {
    printf("Rendering...\n");
    drawPlayer(player);
    tdrawWall(wall1);
    drawWall(wall2);
    drawWall(wall3);
    drawWall(wall4);
    drawDebugOverlay();
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