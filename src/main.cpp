//
//  main.cpp
//  test
//
//  Created by Fiskie on 21/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "Game.h"

int main(int argc, const char *argv[]) {
    Game *game = new Game();

    Map *map = new Map();

    Brush *wall1 = new Brush();
    Brush *wall2 = new Brush();
    Brush *wall3 = new Brush();
    Brush *wall4 = new Brush();

    wall1->loc.x = 200;
    wall2->loc.z = 200;

    wall3->loc.x = 400;
    wall4->loc.z = 400;

    wall1->vol.x = 100;
    wall2->vol.x = 100;
    wall3->vol.x = 100;
    wall4->vol.x = 100;

    wall1->vol.z = 100;
    wall2->vol.z = 100;
    wall3->vol.z = 100;
    wall4->vol.z = 100;

    wall1->vol.y = 100;
    wall2->vol.y = 100;
    wall3->vol.y = 100;
    wall4->vol.y = 100;

    map->addBrush(*wall1);
    map->addBrush(*wall2);
    map->addBrush(*wall3);
    map->addBrush(*wall4);

    game->setMap(map);

    game->run();
    game->exit();
    return 0;
}