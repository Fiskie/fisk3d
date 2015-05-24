//
//  debuggame.h
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#ifndef __fisk3d__debuggame__
#define __fisk3d__debuggame__

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
    void render() override;
    void update(double delta) override;
    void setup() override;

    void drawWall(Wall wall);

    void drawPlayer(Player player);

    void drawDebugInfo();
};

#endif // __fisk3d__debuggame__
