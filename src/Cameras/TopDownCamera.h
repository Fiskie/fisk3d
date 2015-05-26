//
// Created by Fiskie on 26/05/15.
//

#ifndef FISK3D_TOPDOWNCAMERA_H
#define FISK3D_TOPDOWNCAMERA_H


#include "Camera.h"

class TopDownCamera : public Camera {
public:
    TopDownCamera(Game *game);
    void render();
    void drawPlayer(Player *player);
    void drawBrush(Brush *brush);
};


#endif //FISK3D_TOPDOWNCAMERA_H
