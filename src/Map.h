//
// Created by Fiskie on 25/05/15.
//

#ifndef FISK3D_MAP_H
#define FISK3D_MAP_H

#include "World/Brush.h"
#include "World/Wall.h"
#include "Game.h"
#include <list>

class Map {
public:
    std::list<Brush> *brushes;
    std::list<Wall> *walls;

    Map();

    void addBrush(Brush brush);
    void addWall(Wall wall);

    std::list<Brush> *getBrushes() {
        return brushes;
    }

    std::list<Wall> *getWalls() {
        return walls;
    }

    bool isFree(Pos pos);
};

#endif //FISK3D_MAP_H
