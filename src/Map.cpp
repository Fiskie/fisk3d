//
// Created by Fiskie on 25/05/15.
//

#include "Map.h"

void Map::addBrush(Brush brush) {
    brushes->push_back(brush);
}

Map::Map() {
    brushes = new list<Brush>();
}
