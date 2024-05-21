#ifndef BASEBALL_H
#define BASEBALL_H
#include "common_game_defs.h"
#include "BaseObject.h"

class Baseball : public BaseObject
{
public:
    Baseball();
    ~Baseball();

    enum BaseballDir
    {
        DIR_RIGHT = 0,
        DIR_LEFT = 1,
    };

    void set_x_val(const int& xVelo) {x_velo = xVelo;}
    void set_is_move(const bool& isMove) {is_move = isMove;}
    [[nodiscard]] bool get_is_move() const {return is_move;}
    void set_baseball_dir(const unsigned  int& baseballDir) {baseball_dir = baseballDir;}
    void HandleMove(const int& x_border);

private:
    int x_velo;
    bool is_move;
    unsigned int baseball_dir{};

};
#endif //BASEBALL_H
