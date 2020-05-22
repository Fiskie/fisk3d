//
// Created by Fiskie on 25/05/15.
//

#pragma once

#include "World/Brush.h"
#include "World/Wall.h"
#include <list>

struct Map
{
    std::list<Brush> brushes;
    std::list<Wall> walls;

    void addBrush(Brush brush)
    {
        brushes.push_back(brush);
    }
    void addWall(Wall wall)
    {
        walls.push_back(wall);
    }

    bool isFree(Vector3 pos)
    {
        for (auto i = brushes.begin(); i != brushes.end(); ++i)
        {
            if (pos.x > i->pos.x && pos.x < i->pos.x + i->vol.x &&
                pos.z > i->pos.z && pos.z < i->pos.z + i->vol.z)
                return false;
        }

        return true;
    }
};