//
// Created by Fiskie on 24/05/15.
//

#ifndef FISK3D_WALL_H
#define FISK3D_WALL_H

#include "WorldObject.h"
#include "Entity.h"

class Entity;

class Brush : public WorldObject {
public:
    bool collidesWith(Entity *entity);

    bool collidesWith(Pos pos, Pos pos1);
};

#endif //FISK3D_WALL_H
