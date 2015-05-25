//
//  worldobject.h
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#ifndef __fisk3d__worldobject__
#define __fisk3d__worldobject__

#include "Structs.h"
#include <string>

class WorldObject {
public:
    Pos loc;
    Pos rot;
    Pos vol;

    std::string posAsString();
};

#endif //__fisk3d__worldobject__
