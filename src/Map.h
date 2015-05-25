//
// Created by Fiskie on 25/05/15.
//

#ifndef FISK3D_MAP_H
#define FISK3D_MAP_H

#include "Brush.h"
#include "Game.h"
#include <list>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Map {
private:
    std::list<Brush> *brushes;

public:
    Map();
    void addBrush(Brush brush);
    std::list<Brush> *getBrushes() {
        return brushes;
    }

    double getOriginX() {
        return SCREEN_WIDTH / 2;
    }

    double getOriginY() {
        return 0;
    }

    double getOriginZ() {
        return SCREEN_HEIGHT / 2;
    }
};

#endif //FISK3D_MAP_H
