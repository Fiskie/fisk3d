//
//  main.cpp
//  test
//
//  Created by Fiskie on 21/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <SDL2/sdl.h>
#include <SDL2_ttf/sdl_ttf.h>
#include "timer.h"
#include "structs.h"
#include "worldobject.h"
#include "debuggame.h"

int main(int argc, const char * argv[]) {
    DebugGame *game = new DebugGame();
    game->run();
    game->exit();
    return 0;
}