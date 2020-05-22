//
// Created by Fiskie on 24/05/15.
//

#pragma once 

#include "../util/vector.cpp"
#include "../util/printf.h"
#include <string>

class Entity {
public:
    Vector3 loc, rot, vol, vel, acc;
    const char* name;

    std::string posAsString();

    bool collidesWith(Entity *entity);

    bool collidesWith(Vector3 pos, Vector3 pos1);
};

//
// Created by Fiskie on 24/05/15.
//

#include "../Game.h"

std::string Entity::posAsString() {
    return format("Loc (%.2f, %.2f, %.2f) Rot (%.2f, %.2f, %.2f) Vol (%.2f, %.2f, %.2f) Vel (%.2f, %.2f, %.2f)",
                  loc.x, loc.y, loc.z,
                  rot.x, rot.y, rot.z,
                  vol.x, vol.y, vol.z,
                  vel.x, vel.y, vel.z
    );
}

bool Entity::collidesWith(Entity * entity) {
    return collidesWith(entity->loc, entity->vol);
}

bool Entity::collidesWith(Vector3 loc, Vector3 vol) {
    return (abs((int)(this->loc.x - loc.x)) * 2 < (this->vol.x + vol.x)) &&
           (abs((int)(this->loc.z - loc.z)) * 2 < (this->vol.z + vol.z));
}