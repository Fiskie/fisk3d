//
// Created by Fiskie on 26/05/15.
//

#include "Camera.h"
#include "../FatalGameException.h"

Camera::Camera(Game *game) {
    this->game = game;
}

Camera::Camera() {
    font = TTF_OpenFont("OpenSans-Regular.ttf", 11);

    if (font == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        throw new FatalGameException("Could not load required font.");
    }
}

void Camera::drawLabel(string label, int x, int y) {
    SDL_Renderer *renderer = game->getRenderer();
    SDL_Color color;
    const char* str = label.c_str();
    int w;
    int h;

    color.b = 127;
    color.g = 255;
    color.r = 255;
    color.a = 0;

    SDL_Surface *text = TTF_RenderText_Blended(font, str, color);

    // Size our label decently
    TTF_SizeText(font, str, &w, &h);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = w;
    SrcR.h = h;

    DestR.x = x;
    DestR.y = y;
    DestR.w = w;
    DestR.h = h;

    SDL_RenderCopy(renderer, tex, &SrcR, &DestR);
}