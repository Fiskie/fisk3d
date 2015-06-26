//
// Created by Fiskie on 26/05/15.
//

#ifndef FISK3D_CAMERA_H
#define FISK3D_CAMERA_H

#include "../Game.h"
#include <SDL2_ttf/SDL_ttf.h>

using namespace std;

class Game;

class Camera {
protected:
    Game *game;

    Camera();

    TTF_Font *font;
public:
    Camera(Game *game);

    virtual void render() = 0;

    void drawLabel(string label, int x, int y);

    virtual ~Camera();
};

#endif //FISK3D_CAMERA_H
