//
// Created by Fiskie on 26/05/15.
//

#pragma once

#include "../FatalGameException.h"
#include "../Game.h"
#include <SDL2/SDL_ttf.h>

struct Camera {
    Game *game;
    TTF_Font *font;
    SDL_Rect viewport;

    virtual void render() = 0;

    void drawLabel(std::string label, int x, int y) {
        SDL_Renderer *renderer = game->getRenderer();
        SDL_Color color { 255, 255, 127, 0 };
        const char* str = label.c_str();
        int w, h;

        SDL_Surface *text = TTF_RenderText_Blended(font, str, color);

        // Size our label decently
        TTF_SizeText(font, str, &w, &h);

        SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, text);

        SDL_FreeSurface(text);

        // copy entire texture into dest
        SDL_Rect SrcR = {0,0,w,h};
        SDL_Rect DestR = {x,y,w,h};

        SDL_RenderCopy(renderer, tex, &SrcR, &DestR);

        SDL_DestroyTexture(tex);
    }
};