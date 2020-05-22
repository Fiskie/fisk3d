//
// Created by Fiskie on 25/05/15.
//

#pragma once 

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

    bool isFree(Vector3 pos);
};

//
// Created by Fiskie on 25/05/15.
//

void Map::addBrush(Brush brush) {
    brushes->push_back(brush);
}

void Map::addWall(Wall wall) {
    walls->push_back(wall);
}

Map::Map() {
    brushes = new std::list<Brush>();
    walls = new std::list<Wall>();
}

bool Map::isFree(Vector3 pos) {
    std::list<Brush>::iterator i;

    for (i = brushes->begin(); i != brushes->end(); ++i) {
        if (pos.x > i->loc.x && pos.x < i->loc.x + i->vol.x &&
                pos.z > i->loc.z && pos.z < i->loc.z + i->vol.z)
            return false;
    }

    return true;
}