//
// Created by Fiskie on 24/05/15.
//

#ifndef FISK3D_PLAYER_H
#define FISK3D_PLAYER_H

#define MOVEMENT_FORWARD 0
#define MOVEMENT_LEFT 1
#define MOVEMENT_RIGHT 2
#define MOVEMENT_BACKWARD 3

#include "WorldObject.h"
#include <map>

using namespace std;

class Player : public WorldObject {
private:
    map<int, bool> movements;
public:
    Player();
    void addMovement(int id);
    void removeMovement(int id);
    void move();
};

#endif //FISK3D_PLAYER_H
