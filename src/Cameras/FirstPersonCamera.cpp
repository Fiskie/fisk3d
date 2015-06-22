//
// Created by Fiskie on 22/06/15.
//

#include "FirstPersonCamera.h"

void FirstPersonCamera::drawPlayer(Player *player) {
    SDL_Renderer *renderer = game->getRenderer();

    double relX = game->originX - player->vol.x / 2;
    double relZ = game->originZ - player->vol.z / 2;

    SDL_SetRenderDrawColor(renderer, 255, 66, 255, 1);

    SDL_RenderDrawLine(renderer, (int) relX, (int) relZ, (int) (relX + player->vol.x),
                       (int) relZ);
    SDL_RenderDrawLine(renderer, (int) relX, (int) relZ, (int) relX,
                       (int) (relZ + player->vol.z));
    SDL_RenderDrawLine(renderer, (int) (relX + player->vol.x), (int) relZ,
                       (int) (relX + player->vol.x),
                       (int) (relZ + player->vol.z));
    SDL_RenderDrawLine(renderer, (int) relX, (int) (relZ + player->vol.z),
                       (int) (relX + player->vol.x), (int) (relZ + player->vol.z));

    SDL_SetRenderDrawColor(renderer, 255, 255, 66, 1);

    SDL_RenderDrawLine(renderer, game->originX, game->originZ, game->originX,
                       game->originZ - 10);

    // Text...
    string label = format("(%.2f,%.2f)", player->loc.x, player->loc.z);

    drawLabel(label, (int) relX + 5, (int) relZ + 5);
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
        double rX = (tX * pCos - tZ * pSin), rZ = (tX * pSin + tZ * pCos);

        // TODO improve plane clipping
        if (rZ > 0)
            unseenPoints++;

        double xScale = 90 / rX, yScale = 90 / rZ;

        points[i][0] = (int) (oX + tX * xScale);
        points[i][1] = (int) (oZ + tY * yScale);

        drawLabel(format("Screen: (%d, %d) World: (%.2f,%.2f,%.2f)", points[i][0], points[i][1], vertice.x, vertice.y, vertice.z), points[i][0], points[i][1]);
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

    drawPlayer(game->getPlayer());

    drawDebugInfo();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);

    // SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(renderer);
}

FirstPersonCamera::FirstPersonCamera(Game *game) {
    this->game = game;
}

void FirstPersonCamera::drawDebugInfo() {
    drawLabel("fisk3d", 5, 5);
    drawLabel("you're a kid you're a squid", 5, 20);
}
