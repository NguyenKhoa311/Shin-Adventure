#ifndef TIMER_H
#define TIMER_H
#include "common_game_defs.h"

class Timer
{
public:
    Timer();
    ~Timer();

    void start();
    [[nodiscard]] int get_ticks() const;

private:
    int start_tick;
    int paused_tick;

    bool is_paused_;
    bool is_started_;
};

#endif //TIMER_H
