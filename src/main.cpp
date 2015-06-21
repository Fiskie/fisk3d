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
    Brush *wall5 = new Brush();
    Brush *wall6 = new Brush();
    Brush *wall7 = new Brush();

    wall1->vol.x = 600;
    wall1->vol.y = 100;
    wall1->vol.z = 100;
    wall1->placeAt(300, 0, 300);
    wall1->name = "Wall 1";

    wall2->vol.x = 600;
    wall2->vol.y = 100;
    wall2->vol.z = 100;
    wall2->placeAt(200, 0, -300);
    wall2->name = "Wall 2";

    wall3->vol.x = 100;
    wall3->vol.y = 100;
    wall3->vol.z = 600;
    wall3->placeAt(-300, 0, 300);
    wall3->name = "Wall 3";

    wall4->vol.x = 100;
    wall4->vol.y = 100;
    wall4->vol.z = 600;
    wall4->placeAt(300, 0, 200);
    wall4->name = "Wall 4";

    wall5->vol.x = 100;
    wall5->vol.y = 100;
    wall5->vol.z = 300;
    wall5->placeAt(100, 0, 100);
    wall5->name = "Wall 5";

    wall6->vol.x = 100;
    wall6->vol.y = 100;
    wall6->vol.z = 100;
    wall6->placeAt(-100, 0, -100);
    wall6->name = "Wall 6";

    wall7->vol.x = 100;
    wall7->vol.y = 100;
    wall7->vol.z = 100;
    wall7->placeAt(-100, 0, 100);
    wall7->name = "Wall 7";

    map->addBrush(*wall1);
    map->addBrush(*wall2);
    map->addBrush(*wall3);
    map->addBrush(*wall4);
    map->addBrush(*wall5);
    map->addBrush(*wall6);
    map->addBrush(*wall7);

    game->setResolution(1024, 768);
    game->setMap(map);

    game->run();
    return 0;
}