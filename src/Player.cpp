#include <math.h>
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
    double sine = sin(rot.x);
    double cosine = cos(rot.x);

    if ((movements[MOVEMENT_RIGHT] || movements[MOVEMENT_LEFT]) && (movements[MOVEMENT_FORWARD] || movements[MOVEMENT_BACKWARD])) {
        cosine /= 2;
        sine /= 2;
    }

    if (movements[MOVEMENT_RIGHT]) {
        loc.x += cosine;
        loc.z -= sine;
    }

    if (movements[MOVEMENT_LEFT]) {
        loc.x -= cosine;
        loc.z += sine;
    }

    if (movements[MOVEMENT_FORWARD]) {
        loc.x -= sine;
        loc.z -= cosine;
    }

    if (movements[MOVEMENT_BACKWARD]) {
        loc.x += sine;
        loc.z += cosine;
    }
}
