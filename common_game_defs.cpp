#include "common_game_defs.h"

bool GameDef::CheckCollision(const SDL_Rect &obj_a, const SDL_Rect &obj_b) {
    // get obj_a 
    int left_a = obj_a.x;
    int right_a = obj_a.x + obj_a.w;
    int top_a = obj_a.y;
    int bottom_a = obj_a.y + obj_a.h;

    // get obj_b
    int left_b = obj_b.x;
    int right_b = obj_b.x + obj_b.w;
    int top_b = obj_b.y;
    int bottom_b = obj_b.y + obj_b.h;

    // Check for no collision
    if (bottom_a <= top_b || top_a >= bottom_b || right_a <= left_b || left_a >= right_b) {
        return false;
    }
    return true;
}
