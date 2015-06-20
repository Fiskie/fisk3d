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
    speed = 5;
};

void Player::addMovement(int id) {
    movements[id] = true;
}

void Player::removeMovement(int id) {
    movements[id] = false;
}

bool Player::isMoving() {
    return movements[MOVEMENT_RIGHT] || movements[MOVEMENT_LEFT] || movements[MOVEMENT_FORWARD] || movements[MOVEMENT_BACKWARD];
}

void Player::move() {
    if (!isMoving())
        return;

    double iteration = 0;

    while (iteration < speed) {
        double sine = sin(rot.x);
        double cosine = cos(rot.x);

        if (speed - iteration < 1) {
            sine /= iteration;
            cosine /= iteration;
        }

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

        list<Brush> *brushes = game->getMap()->getBrushes();

        list<Brush>::iterator i;

        bool collision = false;

        for (i = brushes->begin(); i != brushes->end(); ++i) {
            if (i->collidesWith(newPos, this->vol)) {
                collision = true;
            }
        }

        // Slide along walls if we walk into them
        Pos tmpPos = newPos;

        // x axis
        if (collision) {
            collision = false;

            tmpPos.x = loc.x;

            for (i = brushes->begin(); i != brushes->end(); ++i) {
                if (i->collidesWith(tmpPos, this->vol)) {
                    collision = true;
                }
            }

            if (!collision)
                newPos = tmpPos;
        }

        // z axis
        if (collision) {
            collision = false;

            tmpPos.x = newPos.x;
            tmpPos.z = loc.z;

            for (i = brushes->begin(); i != brushes->end(); ++i) {
                if (i->collidesWith(tmpPos, this->vol)) {
                    collision = true;
                }
            }

            if (!collision)
                newPos = tmpPos;
        }

        // Update location
        if (!collision) {
            loc.x = newPos.x;
            loc.y = newPos.y;
            loc.z = newPos.z;
        }

        iteration++;
    }
}

void Player::setSpeed(int speed) {
    Player::speed = speed;
}

int Player::getSpeed() const {
    return speed;
}