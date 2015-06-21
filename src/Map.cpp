//
// Created by Fiskie on 25/05/15.
//

#include "Map.h"

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

bool Map::isFree(Pos pos) {
    list<Brush>::iterator i;

    for (i = brushes->begin(); i != brushes->end(); ++i) {
        if (pos.x > i->loc.x && pos.x < i->loc.x + i->vol.x &&
                pos.z > i->loc.z && pos.z < i->loc.z + i->vol.z)
            return false;
    }

    return true;
}