//
//  worldobject.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "WorldObject.h"
#include "Game.h"

using namespace std;

string WorldObject::posAsString() {
    return format("Loc (%.2f, %.2f, %.2f) Rot (%.2f, %.2f, %.2f) Vol (%.2f, %.2f, %.2f)",
                  loc.x, loc.y, loc.z,
                  rot.x, rot.y, rot.z,
                  vol.x, vol.y, vol.z
    );
}