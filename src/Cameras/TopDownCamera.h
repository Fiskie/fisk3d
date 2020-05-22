//
// Created by Fiskie on 26/05/15.
//

#pragma once 

#include "Camera.h"

#define PI 3.14159265

class TopDownCamera : public Camera {
public:
    float zoom = 1.0;

    TopDownCamera(Game *game);
    TopDownCamera(Game *game, SDL_Rect viewport);

    void render();

    void drawPlayer(Player *player);

    void drawBrush(Brush *brush);

    void drawDebugInfo();

    void drawWall(Wall *wall);
};

//
// Created by Fiskie on 26/05/15.
//

void TopDownCamera::drawPlayer(Player *player) {
    SDL_Renderer *renderer = game->getRenderer();

    double relX = viewport.w / 2 - player->vol.x / 2;
    double relZ = viewport.h / 2 - player->vol.z / 2;

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

void TopDownCamera::drawBrush(Brush *brush) {
    SDL_Renderer *renderer = game->getRenderer();
    Player *player = game->getPlayer();

    // Fetch some values we're going to be using a lot.
    double oX = viewport.w / 2;
    double oZ = viewport.h / 2;
    double pCos = player->xRotCos, pSin = player->xRotSin;

    // Get the relative coordinates so the brush gets drawn in the right place.
    double rX = brush->loc.x - player->loc.x - brush->vol.x / 2;
    double rZ = brush->loc.z - player->loc.z - brush->vol.z / 2;

    rX *= zoom;
    rZ *= zoom;

    // Our pairs of brush coordinates.
    int x1 = (int) (oX + (rX * pCos - rZ * pSin));
    int z1 = (int) (oZ + (rX * pSin + rZ * pCos));
    int x2 = (int) (oX + ((rX + brush->vol.x) * pCos - rZ * pSin));
    int z2 = (int) (oZ + ((rX + brush->vol.x) * pSin + rZ * pCos));
    int x3 = (int) (oX + ((rX + brush->vol.x) * pCos - (rZ + brush->vol.z) * pSin));
    int z3 = (int) (oZ + ((rX + brush->vol.x) * pSin + (rZ + brush->vol.z) * pCos));
    int x4 = (int) (oX + (rX * pCos - (rZ + brush->vol.z) * pSin));
    int z4 = (int) (oZ + (rX * pSin + (rZ + brush->vol.z) * pCos));

    // Draw lines.
    SDL_SetRenderDrawColor(renderer, 66, 255, 255, 1);
    SDL_RenderDrawLine(renderer, x1, z1, x2, z2);
    SDL_RenderDrawLine(renderer, x2, z2, x3, z3);
    SDL_RenderDrawLine(renderer, x3, z3, x4, z4);
    SDL_RenderDrawLine(renderer, x4, z4, x1, z1);

    // Text...: Camera(game, viewport) {}
    if (brush->name) {
        drawLabel(format("%s, (%.2f,%.2f)", brush->name, brush->loc.x, brush->loc.z), x1 + 5, z1 + 5);
    } else {
        drawLabel(format("(%.2f,%.2f)", brush->loc.x, brush->loc.z), x1 + 5, z1 + 5);
    }
}

void TopDownCamera::drawWall(Wall *wall) {
    SDL_Renderer *renderer = game->getRenderer();
    Player *player = game->getPlayer();

    // Fetch some values we're going to be using a lot.
    double oX = viewport.w / 2, oZ = viewport.h / 2;
    double pCos = player->xRotCos, pSin = player->xRotSin;

    int points[4][2];

    for (int i = 0; i < 4; i++) {
        Vector3 vertice = wall->getPoint(i);

        // Get the relative coordinates so the brush gets drawn in the right place.
        Vector3 v = vertice.sub(player->loc);

        // Rotate the coordinates around the player's view.
        double tX = v.x * pSin - v.z * pCos * zoom, tY = v.x * pCos + v.z * pSin * zoom;

        points[i][0] = (int) (oX - tX);
        points[i][1] = (int) (oZ - tY);

        drawLabel(format("(%.2f,%.2f)", vertice.x, vertice.z), points[i][0], points[i][1]);
    }

    // Draw lines.
    SDL_SetRenderDrawColor(renderer, 66, 255, 66, 1);
    SDL_RenderDrawLine(renderer, points[0][0], points[0][1], points[1][0], points[1][1]);
    SDL_RenderDrawLine(renderer, points[1][0], points[1][1], points[2][0], points[2][1]);
    SDL_RenderDrawLine(renderer, points[2][0], points[2][1], points[3][0], points[3][1]);
    SDL_RenderDrawLine(renderer, points[3][0], points[3][1], points[0][0], points[0][1]);
}

void TopDownCamera::render() {
    SDL_Renderer *renderer = game->getRenderer();
    SDL_RenderSetViewport(renderer, &viewport);
    Map *map = game->getMap();

    list<Brush> *objs = map->getBrushes();

    // appears to be unused
    //for (auto i = objs->begin(); i != objs->end(); ++i) {
    //    drawBrush(&(*i));
    //}

    list<Wall> *walls = map->getWalls();

    for (auto j = walls->begin(); j != walls->end(); ++j) {
        drawWall(&(*j));
    }

    drawPlayer(game->getPlayer());

    drawDebugInfo();
    SDL_RenderSetViewport(renderer, NULL);
}

void TopDownCamera::drawDebugInfo() {
    drawLabel("fisk3d", 5, 5);
    drawLabel("Top-Down Camera", 5, 20);
}

TopDownCamera::TopDownCamera(Game *game) {
    this->game = game;
    auto r = this->game->getRenderer();
    int w, h;
    SDL_GetRendererOutputSize(r, &w, &h);
    this->viewport = SDL_Rect{0,0,w,h};
}

TopDownCamera::TopDownCamera(Game *game, SDL_Rect viewport) {
    this->game = game;
    this->viewport = viewport;
}