//
//  debuggame.h
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#ifndef __test__debuggame__
#define __test__debuggame__

#include <stdio.h>
#include "game.h"
#include "structs.h"

struct Player {
    Pos loc;
    Pos rot;
    Pos vol;
};

struct Wall {
    Pos loc;
    Pos rot;
    Pos vol;
};

class DebugGame : public Game {
private:
    Player player;
    Wall wall1;
    Wall wall2;
    Wall wall3;
    Wall wall4;
    
public:
    void render();
    void update(double delta);
    void setup();
    void drawWall(Wall wall);
    void drawPlayer(Player player);
};

#endif /* defined(__test__debuggame__) */
