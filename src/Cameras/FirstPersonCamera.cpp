//
// Created by Fiskie on 22/06/15.
//

#include "FirstPersonCamera.h"

void FirstPersonCamera::drawUI() {
    SDL_Renderer *renderer = game->getRenderer();

    SDL_SetRenderDrawColor(renderer, 255, 66, 255, 1);

    SDL_RenderDrawLine(renderer, game->originX - 5, game->originZ, game->originX + 5, game->originZ);
    SDL_RenderDrawLine(renderer, game->originX, game->originZ - 5, game->originX, game->originZ + 5);

}

void FirstPersonCamera::drawWall(Wall *wall) {
    SDL_Renderer *renderer = game->getRenderer();
    Player *player = game->getPlayer();

    // Fetch some values we're going to be using a lot.
    double oX = game->originX;
    double oZ = game->originZ;
    double pCos = cos(player->rot.x);
    double pSin = sin(player->rot.x);

    int points[4][2];

    int unseenPoints = 0;

    for (int i = 0; i < 4; i++) {
        Pos vertice = wall->getPoint(i);

        // Get the coordinates relative the player.
        double tX = vertice.x - player->loc.x, tY = vertice.y - player->loc.y, tZ = vertice.z - player->loc.z;

        // Rotate the coordinates around the player's view.
        double rX = (tX * pCos + tZ * pSin), rY = (tX * pSin + tZ * pCos);

        // TODO improve plane clipping
        if (rY > 0)
            unseenPoints++;

        double xScale = 90 / rY, zScale = 60 / rX;

        if (zScale < 0)
            zScale = 0 - zScale;

        if (xScale < 0)
            xScale = 0 - xScale;

        points[i][0] = (int) (oX + tX * xScale);
        points[i][1] = (int) (oZ - tY * zScale);

        drawLabel(format("Screen: (%d, %d)", points[i][0], points[i][1]), points[i][0], points[i][1]);
        drawLabel(format("World: (%.2f,%.2f,%.2f)", vertice.x, vertice.y, vertice.z), points[i][0], points[i][1] + 15);
        drawLabel(format("Rotated: (%.2f,%.2f)", rX, rY), points[i][0], points[i][1] + 30);
        drawLabel(format("Relative: (%.2f,%.2f,%.2f)", tX, tY, tZ), points[i][0], points[i][1] + 45);
        drawLabel(format("Scale: (%.2f,%.2f)", xScale, zScale), points[i][0], points[i][1] + 60);
    }

    if (unseenPoints == 4)
        return;

    // Draw lines.
    SDL_SetRenderDrawColor(renderer, 66, 255, 66, 1);
    SDL_RenderDrawLine(renderer, points[0][0], points[0][1], points[1][0], points[1][1]);
    SDL_RenderDrawLine(renderer, points[1][0], points[1][1], points[2][0], points[2][1]);
    SDL_RenderDrawLine(renderer, points[2][0], points[2][1], points[3][0], points[3][1]);
    SDL_RenderDrawLine(renderer, points[3][0], points[3][1], points[0][0], points[0][1]);
}

void FirstPersonCamera::render() {
    SDL_Renderer *renderer = game->getRenderer();
    Map *map = game->getMap();

    SDL_RenderClear(renderer);

    list<Wall> *walls = map->getWalls();

    list<Wall>::iterator j;

    for (j = walls->begin(); j != walls->end(); ++j) {
        drawWall(&(*j));
    }

    drawUI();
    drawDebugInfo();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);

    // SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(renderer);
}

FirstPersonCamera::FirstPersonCamera(Game *game) {
    this->game = game;
}

void FirstPersonCamera::drawDebugInfo() {
    Player *player = game->getPlayer();

    drawLabel("fisk3d", 5, 5);
    drawLabel("First Person Camera", 5, 20);
    drawLabel(format("(%.2f,%.2f,%.2f)", player->loc.x, player->loc.y, player->loc.z), 5, 35);
}
