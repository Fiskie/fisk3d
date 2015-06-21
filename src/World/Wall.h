//
// Created by Fiskie on 21/06/15.
//

#ifndef FISK3D_WALL_H
#define FISK3D_WALL_H

#include "../Structs.h"

class Wall {
private:
    Pos points[4];
public:
    Pos getPoint(int i);

    void setPoint(int i, Pos pos);

    void setPoint(int i, double x, double y, double z);
};


#endif //FISK3D_WALL_H
