#ifndef UNDEFINED_GAME_ENEMIES_H
#define UNDEFINED_GAME_ENEMIES_H

#include "common_game_defs.h"
#include "BaseObject.h"
#include "Shinchan.h"

#define ENEMIES_GRAVITY 9
#define MAX_FALL_SPEED 30
#define ENEMY_FRAME 15
#define ENEMY_SPEED 8
#define ENEMY_DAME 10
#define MOVING_ENEMY_HP 150
#define STATIC_ENEMY_HP 100

const int MAX_HEALTH_BAR_LENGTH = 100;

class Enemies : public BaseObject
{
public:
    Enemies();
    ~Enemies();

    enum MoveType
    {
        STATIC = 0,
        MOVE = 1,
    };
    void set_hp(const int& HP) {hp = HP;}
    [[nodiscard]] int get_hp() const {return hp;}
    void set_x_pos(const float& x) {x_pos = x;}
    void set_y_pos(const float& y) {y_pos = y;}
    [[nodiscard]] float get_x_pos() const {return x_pos;}
    void SetMapXY(const int& x, const int& y) {map_x_ = x; map_y_ = y;}
    void set_enemy_count(const int& num) {enemy_count = num;}
    [[nodiscard]] int get_enemy_count() const {return enemy_count;}

    void Set_clips();
    bool LoadImg(const char * path, SDL_Renderer* renderer) override;
    void Show(SDL_Renderer* renderer);
    [[nodiscard]] int get_enemy_hp() const {return hp;}
    SDL_Rect get_enemy_frame();
    void InitEnemies();
    void DoEnemies(Map& map_data);
    void CheckCollision(Map& map_data);
    void set_move_type(const int& MoveType) {move_type = MoveType;}
    [[nodiscard]] MoveType get_move_type() const {return static_cast<MoveType>(move_type);}
    void set_EnemyBor(const float& left, const float& right) {border_left = left; border_right = right;}
    void set_input_left(const int& ipLeft) {input_type.left = ipLeft;}
    void ImpMoveType(SDL_Renderer* renderer);
    static void renderHealthBar(SDL_Renderer* renderer, Enemies* enemy);
    static bool isEmptyTile(int value);

private:
    int comeback_time;
    float x_velo;
    float y_velo;
    float x_pos;
    float y_pos;
    int hp;
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip[ENEMY_FRAME]{};
    Input input_type{};
    int map_x_;
    int map_y_;
    bool on_ground;
    int frame;

    int move_type;
    float border_left;
    float border_right;
    int enemy_count;
};

#endif //UNDEFINED_GAME_ENEMIES_H
