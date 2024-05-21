#ifndef UNDEFINED_GAME_EXPLOSION_H
#define UNDEFINED_GAME_EXPLOSION_H

#include "common_game_defs.h"
#include "BaseObject.h"

#define EXP_FRAME 7

class Explosion : public BaseObject
{
public:
    Explosion();
    ~Explosion();

     void set_clip();
     void set_frame(const int& fr) {frame = fr;}
     bool LoadImg(const char* path, SDL_Renderer* renderer) override;
     void Show(SDL_Renderer* renderer);
     [[nodiscard]] int get_width_frame() const {return width_frame;}
     [[nodiscard]] int get_height_frame() const {return height_frame;}

private:
     int width_frame;
     int height_frame;
     int frame;
     SDL_Rect frame_clip[EXP_FRAME]{};

};

#endif //UNDEFINED_GAME_EXPLOSION_H
