//
// Created by Hoang Nguyen on 29/03/2024.
//

#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "common_game_defs.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect (const int& x,const int& y) {rect.x = x, rect.y = y;}
    [[nodiscard]] SDL_Rect GetRect() const {return rect;}
    [[nodiscard]] SDL_Texture* GetObject() const {return p_object;}

    virtual bool LoadImg(const char * path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = nullptr);
    void Free();
protected:
    SDL_Texture* p_object;
    SDL_Rect rect{};
};
#endif //BASEOBJECT_H
