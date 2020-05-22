//
//  timer.h
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#pragma once

#include <SDL2/SDL_timer.h>

class Timer
{
private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;

public:
    Timer()
    {
        startTicks = 0;
        pausedTicks = 0;
        paused = false;
        started = false;
    }

    void start()
    {
        started = true;
        paused = false;
        startTicks = SDL_GetTicks();
    }

    void stop()
    {
        started = false;
        paused = false;
    }

    void pause()
    {
        if (started && !paused)
        {
            paused = true;
            pausedTicks = SDL_GetTicks() - startTicks;
        }
    }

    void unpause()
    {
        if (paused)
        {
            paused = false;
            startTicks = SDL_GetTicks() - pausedTicks;
            pausedTicks = 0;
        }
    }

    int getTicks()
    {
        if (started)
        {
            return paused ? pausedTicks : SDL_GetTicks() - startTicks;
        }

        return 0;
    }

    bool isStarted() { return started; }
    bool isPaused() { return paused; }
};