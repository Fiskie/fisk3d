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

    Brush *brush1 = new Brush();
    Brush *brush2 = new Brush();
    Brush *brush3 = new Brush();
    Brush *brush4 = new Brush();
    Brush *brush5 = new Brush();
    Brush *brush6 = new Brush();
    Brush *brush7 = new Brush();

    brush1->vol.x = 600;
    brush1->vol.y = 100;
    brush1->vol.z = 100;
    brush1->placeAt(300, 0, 300);
    brush1->name = "Entity Brush 1";

    brush2->vol.x = 600;
    brush2->vol.y = 100;
    brush2->vol.z = 100;
    brush2->placeAt(200, 0, -300);
    brush2->name = "Entity Brush 2";

    brush3->vol.x = 100;
    brush3->vol.y = 100;
    brush3->vol.z = 600;
    brush3->placeAt(-300, 0, 300);
    brush3->name = "Entity Brush 3";

    brush4->vol.x = 100;
    brush4->vol.y = 100;
    brush4->vol.z = 600;
    brush4->placeAt(300, 0, 200);
    brush4->name = "Entity Brush 4";

    brush5->vol.x = 100;
    brush5->vol.y = 100;
    brush5->vol.z = 300;
    brush5->placeAt(100, 0, 100);
    brush5->name = "Entity Brush 5";

    brush6->vol.x = 100;
    brush6->vol.y = 100;
    brush6->vol.z = 100;
    brush6->placeAt(-100, 0, -100);
    brush6->name = "Entity Brush 6";

    brush7->vol.x = 100;
    brush7->vol.y = 100;
    brush7->vol.z = 100;
    brush7->placeAt(-100, 0, 100);
    brush7->name = "Entity Brush 7";

    map->addBrush(*brush1);
    map->addBrush(*brush2);
    map->addBrush(*brush3);
    map->addBrush(*brush4);
    map->addBrush(*brush5);
    map->addBrush(*brush6);
    map->addBrush(*brush7);

    Wall *wall1 = new Wall();
    Wall *wall2 = new Wall();

    wall1->setPoint(0, {0, 0, 0});
    wall1->setPoint(1, {0, 100, 0});
    wall1->setPoint(2, {100, 0, 0});
    wall1->setPoint(3, {100, 100, 0});

    map->addWall(*wall1);

    wall2->setPoint(0, {200, 0, 200});
    wall2->setPoint(1, {300, 100, 300});
    wall2->setPoint(2, {200, 0, 300});
    wall2->setPoint(3, {100, 100, 300});

    map->addWall(*wall2);

    game->setResolution(1024, 768);
    game->setMap(map);

    game->run();
    return 0;
}