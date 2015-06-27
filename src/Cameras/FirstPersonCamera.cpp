//
// Created by Fiskie on 22/06/15.
//

#include "FirstPersonCamera.h"

void FirstPersonCamera::drawUI() {
    SDL_Renderer *renderer = game->getRenderer();

    // Draw a crosshair
    SDL_SetRenderDrawColor(renderer, 255, 66, 255, 1);
    SDL_RenderDrawLine(renderer, game->originX - 5, game->originZ, game->originX + 5, game->originZ);
    SDL_RenderDrawLine(renderer, game->originX, game->originZ - 5, game->originX, game->originZ + 5);
}

void FirstPersonCamera::drawWall(Wall *wall) {
    SDL_Renderer *renderer = game->getRenderer();
    Player *player = game->getPlayer();

    // Fetch some values we're going to be using a lot.
    double oX = game->originX, oZ = game->originZ;
    double pCos = player->xRotCos, pSin = player->xRotSin;
    double fovH = .3f * game->resY, fovV = .3f * game->resY;

    int points[4][2];
    int unseenPoints = 0;

    for (int i = 0; i < 4; i++) {
        Pos vertice = wall->getPoint(i);

        // Get the coordinates relative to the player.
        double vX = vertice.x - player->loc.x, vY = vertice.y - player->loc.y - player->getCameraHeight(), vZ = vertice.z - player->loc.z;

        // Rotate the coordinates around the player's view.
        double tX = vX * pSin - vZ * pCos, tY = vX * pCos + vZ * pSin;

        if (tY <= 0) {
            drawLabel(format("tX: %.2f tY: %.2f", tX, tY), 5, 100);

            float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20;

            Pos i1 = intersect(tX, tY, tX, tY + 1e-1f, -nearside, nearz, -farside, farz);
            Pos i2 = intersect(tX, tY, tX, tY - 1e-1f, nearside, nearz, farside, farz);

            if (tY < nearz) {
                if (i1.y > 0) {
                    //drawLabel(format("Updating coords from (%.2f, %.2f) to (%.9f, %.9f)", tX, tY, i1.x, i1.y), 5, 100);
                    tX = i1.x;
                    tY = i1.y;
                } else {
                    //drawLabel(format("Updating coords from (%.2f, %.2f) to (%.9f, %.9f)", tX, tY, i2.x, i2.y), 5, 115);
                    tX = i2.x;
                    tY = i2.y;
                }

                unseenPoints++;
            }
        }

        // Perform perspective transformation
        double xScale = fovH / tY, zScale = fovV / tY;

        int x = (int) (oX - tX * xScale);
        int z = (int) (oZ - (vY + tY * player->rot.y) * zScale);
        //int z = (int) (oZ - vY * zScale);

        points[i][0] = x;
        points[i][1] = z;

//        drawLabel(format("Screen: (%d, %d)", points[i][0], points[i][1]), points[i][0], points[i][1]);
//        drawLabel(format("World: (%.2f,%.2f,%.2f)", vertice.x, vertice.y, vertice.z), points[i][0], points[i][1] + 15);
//        drawLabel(format("Rotated: (%.2f,%.2f)", tX, tY), points[i][0], points[i][1] + 30);
//        drawLabel(format("Relative: (%.2f,%.2f,%.2f)", vX, vY, vZ), points[i][0], points[i][1] + 45);
//        drawLabel(format("Scale: (%.2f,%.2f)", xScale, zScale), points[i][0], points[i][1] + 60);
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

    auto begin = walls->begin(), end = walls->end();

    for (j = begin; j != end; ++j) {
        drawWall(&(*j));
    }

    drawUI();
    drawDebugInfo();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);

    SDL_RenderPresent(renderer);
}

FirstPersonCamera::FirstPersonCamera(Game *game) {
    this->game = game;
}

void FirstPersonCamera::drawDebugInfo() {
    Player *player = game->getPlayer();

    drawLabel("fisk3d", 5, 5);
    drawLabel("First Person Camera", 5, 20);
    drawLabel(format("Pos: (%.2f,%.2f,%.2f), Rot: (%.2f,%.2f,%.2f)", player->loc.x, player->loc.y, player->loc.z, player->rot.x, player->rot.y, player->rot.z), 5, 35);
    drawLabel(format("Frame: %d", game->frames), 5, 50);
}
