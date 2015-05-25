//
// Created by Fiskie on 25/05/15.
//

#ifndef FISK3D_MAP_H
#define FISK3D_MAP_H

#include "Brush.h"
#include <list>

using namespace std;

class Map {
private:
    list<Brush> *brushes;

public:
    Map();
    void addBrush(Brush brush);
    list<Brush> *getBrushes() {
        return brushes;
    }
};

#endif //FISK3D_MAP_H
