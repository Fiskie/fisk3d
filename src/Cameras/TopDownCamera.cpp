//
// Created by Fiskie on 26/05/15.
//

#include <SDL2_ttf/SDL_ttf.h>
#include "TopDownCamera.h"
#include "../FatalGameException.h"

void TopDownCamera::drawPlayer(Player *player) {
    SDL_Renderer *renderer = game->getRenderer();
    Map *map = game->getMap();

    double relX = map->getOriginX() - player->vol.x / 2;
    double relZ = map->getOriginZ() - player->vol.z / 2;

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

    SDL_RenderDrawLine(renderer, (int) map->getOriginX(), (int) map->getOriginZ(), (int) map->getOriginX(),
                       (int) map->getOriginZ() - 10);

    // Text...
    string label = format("(%.2f,%.2f)", player->loc.x, player->loc.z);

    drawLabel(label, (int) relX + 5, (int) relZ + 5);
}

void TopDownCamera::drawLabel(string label, int x, int z) {
    SDL_Renderer *renderer = game->getRenderer();

    SDL_Color color;

    color.b = 127;
    color.g = 255;
    color.r = 255;
    color.a = 0;

    SDL_Surface *text = TTF_RenderText_Solid(font, label.c_str(), color);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = 70;
    SrcR.h = 15;

    DestR.x = x;
    DestR.y = z;
    DestR.w = 70;
    DestR.h = 15;

    SDL_RenderCopy(renderer, tex, &SrcR, &DestR);
}

void TopDownCamera::drawBrush(Brush *brush) {
    SDL_Renderer *renderer = game->getRenderer();
    Player *player = game->getPlayer();
    Map *map = game->getMap();

    // Fetch some values we're going to be using a lot.
    double oX = map->getOriginX();
    double oZ = map->getOriginZ();
    double pCos = cos(player->rot.x);
    double pSin = sin(player->rot.x);

    // Get the relative coordinates so the brush gets drawn in the right place.
    double rX = brush->loc.x - player->loc.x;
    double rZ = brush->loc.z - player->loc.z;

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
    drawLabel(format("(%.2f,%.2f)", brush->loc.x, brush->loc.z), x1 + 5, z1 + 5);

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

    // drawDebugInfo();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);

    // SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(renderer);
}

TopDownCamera::TopDownCamera(Game *game) {
    this->game = game;
    font = TTF_OpenFont("OpenSans-Regular.ttf", 11);

    if (font == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        throw new FatalGameException("Could not load required font.");
    }
}
