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
    double relY = 0 - player->vol.y / 2;
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
    SDL_Color color;

    color.b = 127;
    color.g = 255;
    color.r = 255;
    color.a = 0;

    std::string label = format("(%.2f,%.2f)", player->loc.x, player->loc.z);

    SDL_Surface *text = TTF_RenderText_Solid(font, label.c_str(), color);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = 70;
    SrcR.h = 15;

    DestR.x = relX;
    DestR.y = relZ + 10;
    DestR.w = 70;
    DestR.h = 15;

    SDL_RenderCopy(renderer, tex, &SrcR, &DestR);
}

void TopDownCamera::drawBrush(Brush *brush) {
    SDL_Renderer *renderer = game->getRenderer();
    Player *player = game->getPlayer();
    Map *map = game->getMap();

    double lX = map->getOriginX() + brush->loc.x - player->loc.x;
    double lY = brush->loc.y + player->loc.y;
    double lZ = map->getOriginZ() + brush->loc.z - player->loc.z;
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

    // Text...
    SDL_Color color;

    color.b = 127;
    color.g = 255;
    color.r = 255;
    color.a = 0;

    std::string label = format("(%.2f,%.2f)", brush->loc.x, brush->loc.z);

    SDL_Surface *text = TTF_RenderText_Solid(font, label.c_str(), color);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = 70;
    SrcR.h = 15;

    DestR.x = lX + 5;
    DestR.y = lZ + 5;
    DestR.w = 70;
    DestR.h = 15;

    SDL_RenderCopy(renderer, tex, &SrcR, &DestR);
}


void TopDownCamera::render() {
    SDL_Renderer *renderer = game->getRenderer();
    Map *map = game->getMap();

    SDL_RenderClear(renderer);

    std::list<Brush> *objs = map->getBrushes();

    std::list<Brush>::iterator i;

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
