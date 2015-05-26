//
// Created by Fiskie on 26/05/15.
//

#ifndef FISK3D_CAMERA_H
#define FISK3D_CAMERA_H

#include "../Game.h"

class Game;

class Camera {
protected:
    Game *game;
    Camera();
public:
    Camera(Game *game);
    virtual void render() = 0;
};


#endif //FISK3D_CAMERA_H
