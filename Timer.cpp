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
