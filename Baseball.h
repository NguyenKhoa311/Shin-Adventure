//
// Created by Hoang Nguyen on 06/04/2024.
//

#ifndef BASEBALL_H
#define BASEBALL_H
#include "BaseObject.h"
#include "common_game_defs.h"

class Baseball : public BaseObject
{
public:
    Baseball();
    ~Baseball();

    enum BaseballDir
    {
        DIR_RIGHT = 10,
        DIR_LEFT = 11,
    };

    void set_x_val(const int& xVal) {x_val = xVal;}
    [[nodiscard]] int get_x_val() const {return x_val;}

    void set_is_move(const bool& isMove) {is_move = isMove;}
    [[nodiscard]] bool get_is_move() const {return is_move;}

    void set_baseball_dir(const unsigned  int& baseballDir) {baseball_dir = baseballDir;}
    [[nodiscard]] unsigned int get_baseball_dir() const {return baseball_dir;}
    void HandleMove(const int& x_border);

private:
    int x_val;
    bool is_move;
    unsigned int baseball_dir{};

};
#endif //BASEBALL_H
