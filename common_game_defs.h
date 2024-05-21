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

// global variable
static SDL_Window* g_window = nullptr;
static SDL_Renderer* g_renderer = nullptr;
static SDL_Event g_event;
static Mix_Music* music;
static Mix_Music* menu_ms;
static Mix_Chunk* punch;
static Mix_Chunk* throw_ball;
static Mix_Chunk* button_sound;
static Mix_Chunk* choose;
static Mix_Chunk* shin_uoo;
static Mix_Chunk* game_over;
static Mix_Chunk* win;
static Mix_Chunk* star_sound;
static Mix_Chunk* hit;

//screen
const int SCREEN_WIDTH = 1050; // 15 tiles
const int SCREEN_HEIGHT = 700; // 10 tiles
const int FRAME_PER_SECOND = 15;
const int TIME_PER_FRAME = 1000 / FRAME_PER_SECOND;
#define WINDOW_TITLE "Shin-chan Adventure"

// map

#define TILE_SIZE 70
#define MAX_MAP_X 250
#define MAX_MAP_Y 12
#define MAX_TILE 25
#define BLANK_TILE 0
#define STAR 20
#define FRAMES 10
#define BUSHES1 13
#define BUSHES2 14
#define TREE 15
#define DIRECT_BOARD 17
#define BUSHES3 18
#define BUSHES4 19
#define STAR 20


static const std::vector<int> checkValues = {BLANK_TILE, TREE, DIRECT_BOARD, BUSHES1, BUSHES2, BUSHES3, BUSHES4};
static const std::vector<int> enemy_checkValues = {BLANK_TILE, TREE, DIRECT_BOARD, BUSHES1, BUSHES2, BUSHES3, BUSHES4, STAR};

// speed
#define GRAVITY_SPEED 9
#define MAX_FALL_SPEED 30

// MENU
#define MENU_ITEM 3
#define PLAY 0
#define EXIT 1
#define INFO 2

// END_MENU
#define RESTART 0
#define BACK 2

struct Map
{
    int start_x;
    int start_y;
    int max_x;
    int max_y;
    int tiles[MAX_MAP_Y][MAX_MAP_X];
};

struct Input
{
    int left;
    int right;
    int jump;
    int attack;
};

namespace GameDef {
    bool CheckCollision(const SDL_Rect &obj1, const SDL_Rect &obj2);
}

#endif //COMMON_GAME_DEFS_H
