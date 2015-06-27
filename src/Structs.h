//
//  structs.h
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#ifndef __fisk3d__structs__
#define __fisk3d__structs__

#include <stdio.h>
#define vxs(x1, y1, x2, y2) ((x1)*(y2) - (x2)*(y1))
//#define overlap(a0, a1, b0, b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0, a1))

struct Pos {
    double x = 0;
    double y = 0;
    double z = 0;
};

Pos intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

#endif //__fisk3d__structs__
