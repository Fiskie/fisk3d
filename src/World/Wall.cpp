//r
// Created by Fiskie on 21/06/15.
//

#include "Wall.h"

Pos Wall::getPoint(int i) {
    return points[i];
}

void Wall::setPoint(int i, Pos pos) {
    points[i] = pos;
}

void Wall::setPoint(int i, double x, double y, double z) {
    points[i] = {x, y, z};
}