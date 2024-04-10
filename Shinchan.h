//
// Created by Hoang Nguyen on 28/03/2024.
//

#ifndef SHINCHAN_H
#define SHINCHAN_H

#include <utility>
#include "common_game_defs.h"
#include "BaseObject.h"
#include "Baseball.h"

#define GRAVITY_SPEED 9
#define MAX_FALL_SPEED 30
#define SHIN_SPEED 20
#define SHIN_JUMP 50
class Shin : public BaseObject
{
public:
    Shin();
    ~Shin();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
//        FALL = 2,
    };

    bool LoadImg(const char * path, SDL_Renderer* screen) override;
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void UpdatePlayer(SDL_Renderer* des);
    void set_clips();

    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x, map_y_ = map_y;}
    void CenterEntityOnMap(Map& map_data) const;

    void set_baseball_list(std::vector<Baseball*> baseball_list) {p_baseball_list = std::move(baseball_list);}
    [[nodiscard]] std::vector<Baseball*> get_baseball_list() const {return p_baseball_list;}
    void HandleBaseball(SDL_Renderer* des);
    void Count_star();
private:

    int star_count;
    std::vector<Baseball*> p_baseball_list;
    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[10]{};

    Input input_type{};
    int frame;
    int status;
    bool on_ground;

    int map_x_;
    int map_y_;

    int comeback_time;
};

#endif //SHINCHAN_H
