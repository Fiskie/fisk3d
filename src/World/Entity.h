//
// Created by Fiskie on 24/05/15.
//

#pragma once

#include "../util/vector.cpp"
#include "../util/printf.h"
#include <string>

class Entity
{
public:
    Vector3 pos, rot, vol, vel, acc;
    const char *name;

    std::string posAsString()
    {
        return format("Loc (%.2f, %.2f, %.2f) Rot (%.2f, %.2f, %.2f) Vol (%.2f, %.2f, %.2f) Vel (%.2f, %.2f, %.2f)",
                      pos.x, pos.y, pos.z,
                      rot.x, rot.y, rot.z,
                      vol.x, vol.y, vol.z,
                      vel.x, vel.y, vel.z);
    }

    bool collidesWith(Entity *entity)
    {
        return collidesWith(entity->pos, entity->vol);
    }

    bool collidesWith(Vector3 pos, Vector3 vol)
    {
        return (
            (abs((int)(this->pos.x - pos.x)) * 2 < (this->vol.x + vol.x)) &&
            (abs((int)(this->pos.z - pos.z)) * 2 < (this->vol.z + vol.z)));
    }
};