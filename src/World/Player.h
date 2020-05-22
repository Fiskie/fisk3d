//
// Created by Fiskie on 24/05/15.
//

#pragma once 

#include "Actions.h"
#include "Entity.h"
#include <map>
#include "../Game.h"
#include <math.h>

using namespace std;

class Game;

class Player : public Entity {
private:
    map<int, bool> movements;
    Game *game;
    int speed;
    int sprintSpeed;
    int crouchSpeed;
    int jumpForce;

    void accelerate();
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

    void decelerate();
};

//
// Created by Fiskie on 24/05/15.
//
Player::Player(Game* game) {
    this->game = game;
    movements[ACTION_MOVE_RIGHT] = false;
    movements[ACTION_MOVE_LEFT] = false;
    movements[ACTION_MOVE_FORWARD] = false;
    movements[ACTION_MOVE_BACKWARD] = false;
    movements[ACTION_MOVE_UP] = false;
    movements[ACTION_MOVE_DOWN] = false;
    movements[ACTION_CROUCH] = false;
    speed = 5;
    sprintSpeed = 10;
    crouchSpeed = 2;
};

double Player::getCameraHeight() {
    return loc.y + (movements[ACTION_CROUCH] ? 50 : 80);
}

void Player::addMovement(int id) {
    movements[id] = true;
}

void Player::removeMovement(int id) {
    movements[id] = false;
}

bool Player::isMoving() {
    return movements[ACTION_MOVE_RIGHT] || movements[ACTION_MOVE_LEFT] || movements[ACTION_MOVE_FORWARD] || movements[ACTION_MOVE_BACKWARD] || movements[ACTION_MOVE_UP] || movements[ACTION_MOVE_DOWN];
}

void Player::accelerate() {
    // todo: use acc vector instead of directly modifying vel
    double sine = xRotSin, cosine = xRotCos;

    double maxVelocity = speed;

    if (movements[ACTION_SPRINT])
        maxVelocity = sprintSpeed;

    if (movements[ACTION_CROUCH])
        maxVelocity = crouchSpeed;

    if (movements[ACTION_MOVE_RIGHT]) {
        vel.x -= sine;
        vel.z += cosine;
    }

    if (movements[ACTION_MOVE_LEFT]) {
        vel.x += sine;
        vel.z -= cosine;
    }

    if (movements[ACTION_MOVE_FORWARD]) {
        vel.x += cosine;
        vel.z += sine;
    }

    if (movements[ACTION_MOVE_BACKWARD]) {
        vel.x -= cosine;
        vel.z -= sine;
    }

    if (movements[ACTION_MOVE_UP]) {
        vel.y += 1;
    }

    if (movements[ACTION_MOVE_DOWN]) {
        vel.y += -1;
    }

    // Clamp values
    if (vel.x > maxVelocity)
        vel.x = maxVelocity;
    else if (vel.x < -maxVelocity)
        vel.x = -maxVelocity;

    if (vel.z > maxVelocity)
        vel.z = maxVelocity;
    else if (vel.z < -maxVelocity)
        vel.z = -maxVelocity;
}

void Player::decelerate() {
    if (vel.x > 0.1 || vel.x < -0.1)
        vel.x *= 0.80;
    else
        vel.x = 0;

    if (vel.z > 0.1 || vel.z < -0.1)
        vel.z *= 0.80;
    else
        vel.z = 0;
}

void Player::move() {
    accelerate();

    loc.x += vel.x;
    loc.y += vel.y;
    loc.z += vel.z;

    decelerate();

    /*
    if (!isMoving())
        return;

    double iteration = 0;

    int speed = this->speed;

    if (movements[ACTION_SPRINT])
        speed = sprintSpeed;

    if (movements[ACTION_CROUCH])
        speed /= 2;

    double sine = xRotSin;
    double cosine = xRotCos;

    while (iteration < speed) {

        if (speed - iteration < 1) {
            sine /= iteration;
            cosine /= iteration;
        }

        Vector3 newPos;

        newPos.x = loc.x;
        newPos.y = loc.y;
        newPos.z = loc.z;

        if ((movements[ACTION_MOVE_RIGHT] || movements[ACTION_MOVE_LEFT]) && (movements[ACTION_MOVE_FORWARD] || movements[ACTION_MOVE_BACKWARD])) {
            cosine *= 0.9;
            sine *= 0.9;
        }

        if (movements[ACTION_MOVE_RIGHT]) {
            newPos.x -= sine;
            newPos.z += cosine;
        }

        if (movements[ACTION_MOVE_LEFT]) {
            newPos.x += sine;
            newPos.z -= cosine;
        }

        if (movements[ACTION_MOVE_FORWARD]) {
            newPos.x += cosine;
            newPos.z += sine;
        }

        if (movements[ACTION_MOVE_BACKWARD]) {
            newPos.x -= cosine;
            newPos.z -= sine;
        }

        if (movements[ACTION_MOVE_UP]) {
            newPos.y += 1;
        }

        if (movements[ACTION_MOVE_DOWN]) {
            newPos.y += -1;
        }

        bool collision = false;

        list<Wall> *walls = game->getMap()->walls;

        list<Wall>::iterator i;

        //auto begin = walls->begin(), end = walls->end();

        /*
        list<Brush> *brushes = game->getMap()->getBrushes();

        list<Brush>::iterator i;

        for (i = brushes->begin(); i != brushes->end(); ++i) {
            if (i->collidesWith(newPos, this->vol)) {
                collision = true;
            }
        }

        // Slide along walls if we walk into them
        Vector3 tmpPos = newPos;

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
        }*/

    /*
        // Update location
        if (!collision) {
            loc.x = newPos.x;
            loc.y = newPos.y;
            loc.z = newPos.z;
        }

        iteration++;
    }*/
}

void Player::setSpeed(int speed) {
    Player::speed = speed;
}

int Player::getSpeed() const {
    return speed;
}

void Player::setSprintSpeed(int speed) {
    Player::sprintSpeed = speed;
}

int Player::getSprintSpeed() const {
    return sprintSpeed;
}