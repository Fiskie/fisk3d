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
#include "Game.h"
#include "Structs.h"
#include "Player.h"
#include "Wall.h"

class DebugGame : public Game {
private:
    Player *player;
    Wall *wall1;
    Wall *wall2;
    Wall *wall3;
    Wall *wall4;

public:
    virtual void render() override;

    virtual void update(double delta) override;

    virtual void setup() override;

    void drawWall(Wall *wall);

    void drawPlayer(Player *player);

    void drawDebugInfo();

    Player* getPlayer();
};

#endif // __fisk3d__debuggame__
