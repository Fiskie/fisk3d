//
// Created by Fiskie on 26/05/15.
//

#include "TopDownCamera.h"

void TopDownCamera::drawPlayer(Player *player) {
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

void TopDownCamera::drawBrush(Brush *brush) {
    SDL_Renderer *renderer = game->getRenderer();
    Player *player = game->getPlayer();

    // Fetch some values we're going to be using a lot.
    double oX = game->originX;
    double oZ = game->originZ;
    double pCos = cos(player->rot.x);
    double pSin = sin(player->rot.x);

    // Get the relative coordinates so the brush gets drawn in the right place.
    double rX = brush->loc.x - player->loc.x - brush->vol.x / 2;
    double rZ = brush->loc.z - player->loc.z - brush->vol.z / 2;

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

    // Text...
    if (brush->name) {
        drawLabel(format("%s, (%.2f,%.2f)", brush->name, brush->loc.x, brush->loc.z), x1 + 5, z1 + 5);
    } else {
        drawLabel(format("(%.2f,%.2f)", brush->loc.x, brush->loc.z), x1 + 5, z1 + 5);
    }
}

void TopDownCamera::render() {
    SDL_Renderer *renderer = game->getRenderer();
    Map *map = game->getMap();

    SDL_RenderClear(renderer);

    list<Brush> *objs = map->getBrushes();

    list<Brush>::iterator i;

    for (i = objs->begin(); i != objs->end(); ++i) {
        drawBrush(&(*i));
    }

    drawPlayer(game->getPlayer());

    TopDownCamera::drawDebugInfo();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);

    // SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(renderer);
}

TopDownCamera::TopDownCamera(Game *game) {
    this->game = game;
}

void TopDownCamera::drawDebugInfo() {
    drawLabel("fisk3d", 5, 5);
    drawLabel("you're a kid you're a squid", 5, 20);
}
