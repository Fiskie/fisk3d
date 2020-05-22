#pragma once

#include "Player.h"
#include "../Map.h"

// game state, decoupled from Game.h
// todo: use
struct State {
    Player *player;
    Map *map;
};