//
// Created by Fiskie on 24/05/15.
//

#pragma once 

#include "Entity.h"

class Brush : public Entity {
public:
    void placeAt(double x, double y, double z) {
        this->pos.x = x - this->vol.x / 2;
        this->pos.y = y - this->vol.y / 2;
        this->pos.z = z - this->vol.z / 2;
    }
};