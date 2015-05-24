//
//  main.cpp
//  test
//
//  Created by Fiskie on 21/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include "DebugGame.h"

int main(int argc, const char* argv[]) {
    DebugGame* game = new DebugGame();
    game->run();
    game->exit();
    return 0;
}