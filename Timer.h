//
// Created by Hoang Nguyen on 31/03/2024.
//

#ifndef TIMER_H
#define TIMER_H
#include "common_game_defs.h"

class Timer
{
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    [[nodiscard]] int get_ticks() const;
    [[nodiscard]] bool is_started() const;
    [[nodiscard]] bool is_paused() const;

private:
    int start_tick;
    int paused_tick;

    bool is_paused_;
    bool is_started_;
};

#endif //TIMER_H
