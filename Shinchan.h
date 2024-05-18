#ifndef SHINCHAN_H
#define SHINCHAN_H

#include <utility>
#include "common_game_defs.h"
#include "BaseObject.h"
#include "Baseball.h"

#define SHIN_JUMP 50
#define SHIN_SPEED 20
#define SHIN_DAME 50
#define SHIN_HP 100
#define REPEL_DISTANCE 6

class Shin : public BaseObject
{
public:
    Shin();
    ~Shin();

    enum STATE
    {
        RUN_RIGHT = 0,
        RUN_LEFT = 1,
        HIT_LEFT  = 2,
        HIT_RIGHT = 3,
    };

    bool LoadImg(const char* path, SDL_Renderer* renderer) override;
    void UpdateFrame(SDL_Renderer* renderer);
    void HandleInput(SDL_Renderer* renderer, SDL_Event events);
    void HandleKeyDown(SDL_Renderer* renderer, SDL_Keycode key);
    void HandleKeyUp(SDL_Keycode key);
    void HandleHitState(SDL_Renderer* renderer);
    void HandleAttack(SDL_Renderer* renderer);
    void HandleAttackState(SDL_Renderer* renderer);
    void HandleMoveState(SDL_Renderer* renderer);
    void UpdateJumpState(SDL_Renderer* renderer);
    void UpdateGroundState(SDL_Renderer* renderer);
    void UpdateState(SDL_Renderer* renderer);
    void set_clips();
    void set_Shin_hp(const int& HP) {hp = HP;}
    [[nodiscard]] int get_Shin_hp() const {return hp;}
    void set_Shin_state(const int&state) {Shin_state = state;}
    void RenderHealthBar(SDL_Renderer* renderer) const;
    SDL_Rect get_Shin_frame();
    [[nodiscard]] float get_x_pos() const {return x_pos;}
    [[nodiscard]] int get_hit_time() const {return HIT_TIME;}
    Uint32 set_lastHitTime(const Uint32& time) {return lastHitTime = time;}
    [[nodiscard]] Uint32 get_lastHitTime() const {return lastHitTime;}
    [[nodiscard]] bool get_die_state() const {return die;}

    static bool isEmptyTile(int value);
    void Action(Map& map_data, Mix_Chunk* star_s);
    void CheckCollision(Map& map_data, Mix_Chunk* star_sound);
    void CheckHorizontalCollision(Map &map_data, Mix_Chunk* star_sound);
    void CheckVerticalCollision(Map &map_data, Mix_Chunk* star_sound);
    void CheckTileCollision(Map &map_data, Mix_Chunk* star_sound, int y1, int x1, int y2, int x2, float* pos, int reset_pos, bool vertical);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x, map_y_ = map_y;}
    void CenterOnShin(Map& map_data) const;

    // baseball func
    [[nodiscard]] std::vector<Baseball*> get_baseball_list() const {return p_baseball_list;}
    void HandleBaseball(SDL_Renderer* renderer, Mix_Chunk* throw_s);
    void RemoveBaseball(const int& idx);
    // star func
    void Count_star();
    [[nodiscard]] int get_star_count() const {return star_count;}

private:
    int star_count;
    std::vector<Baseball*> p_baseball_list;
    float x_speed;
    float y_speed;
    float x_pos;
    float y_pos;
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip[FRAMES]{};
    Input input_type{};
    int frame;
    int Shin_state;
    bool on_ground;
    bool has_attacked;
    bool being_hit;
    int map_x_;
    int map_y_;
    int hp;
    bool die;
    const int HIT_TIME = 500;
    Uint32 lastHitTime = 0;
};

#endif //SHINCHAN_H
