//
// Created by Hoang Nguyen on 21/03/2024.
//

#ifndef COMMON_GAME_DEFS_H
#define COMMON_GAME_DEFS_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <strstream>


static SDL_Window* g_window = nullptr;
static SDL_Renderer* g_screen = nullptr;
static SDL_Event g_event;

//screen
const int SCREEN_WIDTH = 1050; // 15 tiles
const int SCREEN_HEIGHT = 700; // 10 tiles
const int FRAME_PER_SECOND = 15;
// tile_size 70x70
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0xff;

#define WINDOW_TITLE "Shin-chan phiêu lưu"
#define TILE_SIZE 70
#define MAX_MAP_X 300
#define MAX_MAP_Y 10
#define MAX_TILE 10
#define BLANK_TILE 0
#define STAR 7
#define FRAMES 10

struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    const char* file_name_;
};

struct Input
{
    int left;
    int right;
    int jump;
    int attack;
};

#endif //COMMON_GAME_DEFS_H
