#include "Explosion.h"

Explosion::Explosion() {
    width_frame = 0;
    height_frame = 0;
    frame = 0;
}

Explosion::~Explosion() = default;

bool Explosion::LoadImg(const char *path, SDL_Renderer* renderer) {
    bool load = BaseObject::LoadImg(path, renderer);
    if(load)
    {
        width_frame = rect.w / EXP_FRAME;
        height_frame = rect.h;
    }
    return load;
}

void Explosion::set_clip() {
    if(width_frame > 0 && height_frame > 0)
    {
        for(int i = 0; i < EXP_FRAME; i++)
        {
            frame_clip[i].x = i * width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame - 7;
            frame_clip[i].h = height_frame;
        }
    }
}

void Explosion::Show(SDL_Renderer* renderer) {
    SDL_Rect* current_clip = &frame_clip[frame];
    SDL_Rect render_quad = {rect.x, rect.y, width_frame, height_frame};
    if(current_clip != nullptr)
    {
        render_quad.w = current_clip->w;
        render_quad.h = current_clip->h;
    }

    SDL_RenderCopy(renderer, p_object, current_clip, &render_quad);
}

