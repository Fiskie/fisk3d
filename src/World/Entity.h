//
// Created by Fiskie on 24/05/15.
//

#ifndef FISK3D_ENTITY_H
#define FISK3D_ENTITY_H

#include "../Structs.h"
#include <string>

class Entity {
public:
    Pos loc;
    Pos rot;
    Pos vol;
    const char* name;

    std::string posAsString();

    bool collidesWith(Entity *entity);

    bool collidesWith(Pos pos, Pos pos1);
};

#endif //FISK3D_ENTITY_H
