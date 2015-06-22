//
// Created by Fiskie on 22/06/15.
//

#ifndef FISK3D_FIRSTPERSONCAMERA_H
#define FISK3D_FIRSTPERSONCAMERA_H

#include "Camera.h"

class FirstPersonCamera : public Camera {
public:
    FirstPersonCamera(Game *game);

    void render();

    void drawDebugInfo();

    void drawWall(Wall *wall);

    void drawUI();
};

#endif //FISK3D_FIRSTPERSONCAMERA_H
