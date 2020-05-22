//
//  main.cpp
//  test
//
//  Created by Fiskie on 21/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "Game.h"

void generateTunnel(Map *map, Vector3 o, int length, int width, int height) {
    // the previous 2015 code would put these on the heap,
    // this version uses structs and simple copy-on-write
    // it's less code and less prone to memory leaks
    Wall wall1;
    wall1.setPoint(0, o);
    wall1.setPoint(1, {o.x, o.y + height, o.z});
    wall1.setPoint(2, {o.x + length, o.y + height, o.z});
    wall1.setPoint(3, {o.x + length, o.y, o.z});

    Wall wall2 = wall1;
    wall2.translate(0,0,width);

    Wall corner1 = wall1;
    corner1.translate(0, height, 0);
    corner1.translatePoint(1, 0, 50-height, 50);
    corner1.translatePoint(2, 0, 50-height, 50);

    Wall corner2 = wall2;
    corner2.translate(0, height, 0);
    corner2.translatePoint(1, 0, 50-height, -50);
    corner2.translatePoint(2, 0, 50-height, -50);

    Wall floor;
    floor.setPoint(0, o);
    floor.setPoint(1, {o.x, o.y, o.z + width});
    floor.setPoint(2, {o.x + length, o.y, o.z + width});
    floor.setPoint(3, {o.x + length, o.y, o.z});

    Wall ceil = floor;
    ceil.translatePoint(1, 0, height + 50, -50);
    ceil.translatePoint(2, 0, height + 50, -50);
    ceil.translatePoint(0, 0, height + 50, 50);
    ceil.translatePoint(3, 0, height + 50, 50);

    map->addWall(wall1);
    map->addWall(corner1);
    map->addWall(ceil);
    map->addWall(wall2);
    map->addWall(corner2);
    map->addWall(floor);
}

int main(int argc, const char *argv[]) {
    Game *game = new Game();

    Map *map = new Map();

    generateTunnel(map, {100, 0, 100}, 400, 100, 200);

    generateTunnel(map, {100, 0, 250}, 600, 200, 300);

    generateTunnel(map, {100, 0, 500}, 200, 400, 100);

    Wall floor;
    floor.setPoint(0, {100, 0, -400});
    floor.setPoint(1, {-400, 0, -400});
    floor.setPoint(2, {-400, 0, 900});
    floor.setPoint(3, {100, 0, 900});

    map->addWall(floor);

    game->setResolution(900, 600);
    game->setMap(map);

    game->run();
    return 0;
}