//
// Created by Fiskie on 24/05/15.
//

#include <stdlib.h>
#include "Brush.h"

bool Brush::collidesWith(Entity * entity) {
    return collidesWith(entity->loc, entity->vol);
}

bool Brush::collidesWith(Pos loc, Pos vol) {
    return (abs(this->loc.x - loc.x) * 2 < (this->vol.x + vol.x)) &&
           (abs(this->loc.z - loc.z) * 2 < (this->vol.z + vol.z));
}