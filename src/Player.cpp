#include "Player.h"

//
// Created by Fiskie on 24/05/15.
//
Player::Player() {
    movements = *new map<int, bool>();
    movements[MOVEMENT_RIGHT] = false;
    movements[MOVEMENT_LEFT] = false;
    movements[MOVEMENT_FORWARD] = false;
    movements[MOVEMENT_BACKWARD] = false;
};

void Player::addMovement(int id) {
    movements[id] = true;
}

void Player::removeMovement(int id) {
    movements[id] = false;
}

void Player::move() {
    if (movements[MOVEMENT_RIGHT])
        loc.x += 1;

    if (movements[MOVEMENT_LEFT])
        loc.x -= 1;

    if (movements[MOVEMENT_FORWARD])
        loc.z -= 1;

    if (movements[MOVEMENT_BACKWARD])
        loc.z += 1;
}
