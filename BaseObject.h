
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
    [[nodiscard]] virtual SDL_Texture* GetObject() const {return p_object;}

    virtual bool LoadImg(const char * path, SDL_Renderer* renderer);
    virtual void SetPos(SDL_Rect &button, const int &x, const int &y, const int &w, const int &h);
    void Render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr);
    void Render(SDL_Renderer* renderer, int x, int y, int width, int height, const SDL_Rect *clip);
    virtual void Render(SDL_Renderer* renderer, int x, int y);
    virtual void Render(SDL_Renderer* renderer, const SDL_Rect* src, const SDL_Rect* dst);
    void Free();
protected:
    SDL_Texture* p_object;
    SDL_Rect rect{};
};

#endif //BASEOBJECT_H
