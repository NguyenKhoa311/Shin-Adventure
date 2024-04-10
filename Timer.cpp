//
// Created by Hoang Nguyen on 31/03/2024.
//
#include "Timer.h"

Timer::Timer() {
    start_tick = 0;
    paused_tick = 0;
    is_paused_ = false;
    is_started_ = false;
}

Timer::~Timer() = default;

void Timer::start() {
    is_started_ = true;
    is_paused_ = false;
    start_tick = (int) SDL_GetTicks();
}

void Timer::stop()
{
    is_paused_ = false;
    is_started_ = false;
}

void Timer::pause() {
    if(is_started_ && !is_paused_)
    {
        is_paused_ = true;
        paused_tick = (int) SDL_GetTicks() - start_tick;
    }
}

void Timer::unpause() {
    if(is_paused_)
    {
        is_paused_ = false;
        start_tick = (int) SDL_GetTicks() - paused_tick;
        paused_tick = 0;
    }
}

int Timer::get_ticks() const {
    if(is_started_)
    {
        if(is_paused_)
        {
            return paused_tick;
        }
        else
        {
            return (int) SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}

bool Timer::is_started() const {
    return is_started_;
}

bool Timer::is_paused() const {
    return is_paused_;
}
