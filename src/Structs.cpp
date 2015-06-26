//
//  structs.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "Structs.h"

Pos intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    Pos pos;

    pos.x = vxs(vxs(x1,y1,x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));
    pos.y = vxs(vxs(x1,y1,x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));

    return pos;
}