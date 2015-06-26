//
// Created by Fiskie on 24/05/15.
//

#ifndef FISK3D_PLAYER_H
#define FISK3D_PLAYER_H

#define ACTION_MOVE_FORWARD 0
#define ACTION_MOVE_LEFT 1
#define ACTION_MOVE_RIGHT 2
#define ACTION_MOVE_BACKWARD 3
#define ACTION_SPRINT 4
#define ACTION_MOVE_UP 5
#define ACTION_MOVE_DOWN 6
#define ACTION_CROUCH 7

#include "Entity.h"
#include <map>
#include "../Game.h"

using namespace std;

class Game;

class Player : public Entity {
private:
    map<int, bool> movements;
    Game *game;
    int speed;
    int sprintSpeed;
public:
    double xRotCos;
    double xRotSin;

    int getSpeed() const;

    void setSpeed(int speed);

    int getSprintSpeed() const;

    void setSprintSpeed(int speed);

    Player(Game* game);

    void addMovement(int id);

    void removeMovement(int id);

    void move();

    bool isMoving();

    double getCameraHeight();
};

#endif //FISK3D_PLAYER_H