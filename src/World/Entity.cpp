//
// Created by Fiskie on 24/05/15.
//

#include "../Game.h"

std::string Entity::posAsString() {
    return format("Loc (%.2f, %.2f, %.2f) Rot (%.2f, %.2f, %.2f) Vol (%.2f, %.2f, %.2f)",
                  loc.x, loc.y, loc.z,
                  rot.x, rot.y, rot.z,
                  vol.x, vol.y, vol.z
    );
}

bool Entity::collidesWith(Entity * entity) {
    return collidesWith(entity->loc, entity->vol);
}

bool Entity::collidesWith(Pos loc, Pos vol) {
    return (abs((int)(this->loc.x - loc.x)) * 2 < (this->vol.x + vol.x)) &&
           (abs((int)(this->loc.z - loc.z)) * 2 < (this->vol.z + vol.z));
}