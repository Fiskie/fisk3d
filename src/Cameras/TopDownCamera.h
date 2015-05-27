//
// Created by Fiskie on 26/05/15.
//

#ifndef FISK3D_TOPDOWNCAMERA_H
#define FISK3D_TOPDOWNCAMERA_H

#include "Camera.h"

#define PI 3.14159265

class TopDownCamera : public Camera {
private:
    TTF_Font *font;

public:
    TopDownCamera(Game *game);

    void render();

    void drawPlayer(Player *player);

    void drawBrush(Brush *brush);
};


#endif //FISK3D_TOPDOWNCAMERA_H
