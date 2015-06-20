//
// Created by Fiskie on 24/05/15.
//

#ifndef FISK3D_PLAYER_H
#define FISK3D_PLAYER_H

#define MOVEMENT_FORWARD 0
#define MOVEMENT_LEFT 1
#define MOVEMENT_RIGHT 2
#define MOVEMENT_BACKWARD 3

#include "Entity.h"
#include <map>
#include "../Game.h"

using namespace std;

class Game;

class Player : public Entity {
private:
    map<int, bool> movements;
    Game *game;
public:
    Player(Game* game);

    void addMovement(int id);

    void removeMovement(int id);

    void move();

    bool isMoving();
};

#endif //FISK3D_PLAYER_H