//
// Created by Hoang Nguyen on 06/04/2024.
//
#include "Baseball.h"

Baseball::Baseball() {
    x_velo = 0;
    is_move = false;
}

Baseball::~Baseball() = default;

void Baseball::HandleMove(const int &x_border) {
    if(baseball_dir == DIR_RIGHT)
    {
        rect.x += x_velo;
        if(rect.x >= x_border)
        {
            is_move = false;
        }
    }
    else if(baseball_dir == DIR_LEFT)
    {
        rect.x -= x_velo;
        if(rect.x <= 150)
        {
            is_move = false;
        }
    }
}



