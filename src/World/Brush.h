//
// Created by Fiskie on 24/05/15.
//

#ifndef FISK3D_BRUSH_H
#define FISK3D_BRUSH_H

#include "Entity.h"

class Brush : public Entity {
public:
    void placeAt(double x, double y, double z);
};

#endif //FISK3D_BRUSH_H
