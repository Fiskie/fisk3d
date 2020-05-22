//
// Created by Fiskie on 22/06/15.
//

#pragma once 

#include "Camera.h"

class FirstPersonCamera : public Camera {
public:
    FirstPersonCamera(Game *game);
    FirstPersonCamera(Game *game, SDL_Rect viewport);

    void render();

    void drawDebugInfo();

    void drawWall(Wall *wall);

    void drawUI();
};

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
    double oX = viewport.w / 2, oZ = viewport.h / 2;
    double pCos = player->xRotCos, pSin = player->xRotSin;
    double fovH = .73f * game->resY, fovV = .2f * game->resY;

    // todo: remove length-of-4 hardcoding and allow for walls of many edges, this should be doable (?)
    // maybe leave that until after collision is working, that might break some assumptions
    for (int i = 0; i < 4; i++) {
        Edge edge = wall->getEdge(i);
        Vector3 vertice = wall->getPoint(i);

        // Get the coordinates relative to the player.
        Vector3 v1 = edge.first.sub(player->loc);
        v1.y -= player->getCameraHeight();
        Vector3 v2 = edge.second.sub(player->loc);
        v2.y -= player->getCameraHeight();

        // Rotate the coordinates around the player's view.
        Vector3 t1 = {v1.x * pSin - v1.z * pCos, 0, v1.x * pCos + v1.z * pSin};
        Vector3 t2 = {v2.x * pSin - v2.z * pCos, 0, v2.x * pCos + v2.z * pSin};

        // is the wall at least partially in front of the player?
        if (t1.z <= 0 && t2.z <= 0) continue;

        // if it is partially behind the player, clip it against player's view frustrum
        if (t1.z <= 0 || t2.z <= 0) {
            float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20;
            // find intersect between wall and edges
            Vector3 i1 = intersect(t1.x, t1.z, t2.x, t2.z, -nearside, nearz, -farside, farz);
            Vector3 i2 = intersect(t1.x, t1.z, t2.x, t2.z,  nearside, nearz,  farside, farz);
            if (t1.z < nearz) t1 = (i1.z > 0 ? i1 : i2);
            if (t2.z < nearz) t2 = (i1.z > 0 ? i1 : i2);
        }

        // Perform perspective transformation
        double xScale1 = fovH / t1.z, yScale1 = fovV / t1.z;
        double xScale2 = fovH / t2.z, yScale2 = fovV / t2.z;

        int x1 = oX - t1.x * xScale1;
        int x2 = oX - t2.x * xScale2;

        // ? sector stuff, we don't have this yet
        //if (x1 >= x2) continue;

        // y1 and y2 should be based off of first and last values in render wall loop in c example, since it works on vertical lines
        // multiplying by y rot allows for look down/up
        int y1 = oZ - ((v1.y + t1.z * player->rot.y) * yScale1);
        int y2 = oZ - ((v2.y + t2.z * player->rot.y) * yScale2);

        SDL_SetRenderDrawColor(renderer, 66, 255, 66, 1);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

        // drawLabel(format("Screen: (%d, %d)", points[i][0], points[i][1]), points[i][0], points[i][1]);
        // drawLabel(format("World: (%.2f,%.2f,%.2f)", vertice.x, vertice.y, vertice.z), points[i][0], points[i][1] + 15);
        // drawLabel(format("Rotated: (%.2f,%.2f)", tX, tY), points[i][0], points[i][1] + 30);
        // drawLabel(format("Relative: (%.2f,%.2f,%.2f)", vX, vY, vZ), points[i][0], points[i][1] + 45);
        // drawLabel(format("Scale: (%.2f,%.2f)", xScale, zScale), points[i][0], points[i][1] + 60);
    }
}

void FirstPersonCamera::render() {
    SDL_Renderer *renderer = game->getRenderer();
    Map *map = game->getMap();

    list<Wall> *walls = map->getWalls();

    for (auto j = walls->begin(); j != walls->end(); ++j) {
        drawWall(&(*j));
    }

    drawUI();
    drawDebugInfo();
}

void FirstPersonCamera::drawDebugInfo() {
    Player *player = game->getPlayer();

    drawLabel("fisk3d", 5, 5);
    drawLabel("First Person Camera", 5, 20);
    drawLabel(format("Pos: (%.2f,%.2f,%.2f), Rot: (%.2f,%.2f,%.2f)", player->loc.x, player->loc.y, player->loc.z, player->rot.x, player->rot.y, player->rot.z), 5, 35);
    drawLabel(format("Frame: %d", game->frames), 5, 50);
}


FirstPersonCamera::FirstPersonCamera(Game *game) {
    this->game = game;
    auto r = this->game->getRenderer();
    int w, h;
    SDL_GetRendererOutputSize(r, &w, &h);
    this->viewport = SDL_Rect{0,0,w,h};
}

FirstPersonCamera::FirstPersonCamera(Game *game, SDL_Rect viewport) {
    this->game = game;
    this->viewport = viewport;
}