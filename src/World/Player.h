//
// Created by Fiskie on 24/05/15.
//

#pragma once

#include "Actions.h"
#include "Entity.h"
#include <map>
#include "../Game.h"
#include <math.h>

class Game;

class Player : public Entity
{
private:
    std::map<int, bool> movements;
    Game *game;
    int speed;
    int sprintSpeed;
    int crouchSpeed;
    int jumpForce;

    void accelerate()
    {
        // todo: use acc vector instead of directly modifying vel
        double sine = xRotSin, cosine = xRotCos;

        double maxVelocity = speed;

        if (movements[ACTION_SPRINT])
            maxVelocity = sprintSpeed;

        if (movements[ACTION_CROUCH])
            maxVelocity = crouchSpeed;

        if (movements[ACTION_MOVE_RIGHT])
        {
            vel.x -= sine;
            vel.z += cosine;
        }

        if (movements[ACTION_MOVE_LEFT])
        {
            vel.x += sine;
            vel.z -= cosine;
        }

        if (movements[ACTION_MOVE_FORWARD])
        {
            vel.x += cosine;
            vel.z += sine;
        }

        if (movements[ACTION_MOVE_BACKWARD])
        {
            vel.x -= cosine;
            vel.z -= sine;
        }

        if (movements[ACTION_MOVE_UP])
        {
            vel.y += 1;
        }

        if (movements[ACTION_MOVE_DOWN])
        {
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

public:
    double xRotCos;
    double xRotSin;

    Player(Game *game)
    {
        this->game = game;
        speed = 5;
        sprintSpeed = 10;
        crouchSpeed = 2;
    };

    void addMovement(int id)
    {
        movements[id] = true;
    }

    void removeMovement(int id)
    {
        movements.erase(id);
    }

    void move()
    {
        accelerate();

        pos = pos.add(vel);

        decelerate();

        // "gravity"
        if (pos.y > 0)
        {
            pos.y = pos.y - 5 > 0 ? pos.y - 5 : 0;
        }
        else if (movements[ACTION_JUMP])
        {
            vel.y += 20;
        }

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

        newPos.x = pos.x;
        newPos.y = pos.y;
        newPos.z = pos.z;

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

            tmpPos.x = pos.x;

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
            tmpPos.z = pos.z;

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
            pos.x = newPos.x;
            pos.y = newPos.y;
            pos.z = newPos.z;
        }

        iteration++;
    }*/
    }

    double getCameraHeight()
    {
        return pos.y + (movements[ACTION_CROUCH] ? 50 : 80);
    }

    void decelerate()
    {
        if (vel.x > 0.1 || vel.x < -0.1)
            vel.x *= 0.80;
        else
            vel.x = 0;

        if (vel.y > 0.1 || vel.y < -0.1)
            vel.y *= 0.80;
        else
            vel.y = 0;

        if (vel.z > 0.1 || vel.z < -0.1)
            vel.z *= 0.80;
        else
            vel.z = 0;
    }
};