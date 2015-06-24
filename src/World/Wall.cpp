//r
// Created by Fiskie on 21/06/15.
//

#include "Wall.h"

Pos Wall::getPoint(int i) {
    return points[i];
}

/**
 * Set a point to the coordinations in this position
 */
void Wall::setPoint(int i, Pos pos) {
    points[i] = pos;
}

/**
 * Set the point to these coordinates
 */
void Wall::setPoint(int i, double x, double y, double z) {
    points[i] = {x, y, z};
}

/**
 * Flatten a wall along an axis
 */
void Wall::flatten(int axis) {
    int total = 0;

    for (int i = 0; i < 4; i++) {
        switch (axis) {
            default:
                total += points[i].x;
                break;
            case axisY:
                total += points[i].y;
                break;
            case axisZ:
                total += points[i].z;
                break;
        }
    }

    double mean = ((double) total) / 4;

    for (int i = 0; i < 4; i++) {
        switch (axis) {
            default:
                points[i].x = mean;
                break;
            case axisY:
                points[i].y = mean;
                break;
            case axisZ:
                points[i].z = mean;
                break;
        }
    }
}

Wall::Wall() {

}

Wall::Wall(Wall *wall) {
    for (int i = 0; i < 4; i++) {
        points[i] = wall->points[i];
    }
}

void Wall::translate(double x, double y, double z) {
    for (int i = 0; i < 4; i++)
        Wall::translatePoint(i, x, y, z);
}

void Wall::translatePoint(int i, double x, double y, double z) {
    points[i].x += x;
    points[i].y += y;
    points[i].z += z;
}