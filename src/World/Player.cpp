#include <math.h>
#include "Player.h"

//
// Created by Fiskie on 24/05/15.
//
Player::Player(Game* game) {
    this->game = game;
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
    Pos newPos;
    newPos.x = loc.x;
    newPos.y = loc.y;
    newPos.z = loc.z;

    if ((movements[MOVEMENT_RIGHT] || movements[MOVEMENT_LEFT]) && (movements[MOVEMENT_FORWARD] || movements[MOVEMENT_BACKWARD])) {
        cosine /= 2;
        sine /= 2;
    }

    if (movements[MOVEMENT_RIGHT]) {
        newPos.x += cosine;
        newPos.z -= sine;
    }

    if (movements[MOVEMENT_LEFT]) {
        newPos.x -= cosine;
        newPos.z += sine;
    }

    if (movements[MOVEMENT_FORWARD]) {
        newPos.x -= sine;
        newPos.z -= cosine;
    }

    if (movements[MOVEMENT_BACKWARD]) {
        newPos.x += sine;
        newPos.z += cosine;
    }

    // Update location
    if (game->getMap()->isFree(newPos)) {
        loc.x = newPos.x;
        loc.y = newPos.y;
        loc.z = newPos.z;
    }


}
