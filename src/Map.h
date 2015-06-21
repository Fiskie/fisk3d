//
// Created by Fiskie on 25/05/15.
//

#ifndef FISK3D_MAP_H
#define FISK3D_MAP_H

#include "World/Brush.h"
#include "Game.h"
#include <list>

class Map {
private:
    std::list<Brush> *brushes;

public:
    Map();

    void addBrush(Brush brush);

    std::list<Brush> *getBrushes() {
        return brushes;
    }

    bool isFree(Pos pos);
};

#endif //FISK3D_MAP_H
