//
// Created by Fiskie on 26/05/15.
//

#pragma once

#include "../FatalGameException.h"
#include "../Game.h"
#include <SDL2/SDL_ttf.h>

using namespace std;

class Game;

class Camera {
protected:
    Game *game;
    SDL_Rect viewport;

    Camera();

    TTF_Font *font;
public:
    Camera(Game *game);
    Camera(Game *game, SDL_Rect viewport);

    virtual void render() = 0;

    void drawLabel(string label, int x, int y);
};

//
// Created by Fiskie on 26/05/15.
//

// default constructor uses output size of the renderer
Camera::Camera(Game *game) {
    this->game = game;
    auto r = this->game->getRenderer();
    int w, h;
    SDL_GetRendererOutputSize(r, &w, &h);
    this->viewport = SDL_Rect{0,0,w,h};
}

Camera::Camera(Game *game, SDL_Rect viewport) {
    this->game = game;
    this->viewport = viewport;
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

    SDL_DestroyTexture(tex);
}