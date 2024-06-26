#ifndef UNDEFINED_GAME_TEXTOBJECT_H
#define UNDEFINED_GAME_TEXTOBJECT_H

#include "common_game_defs.h"

class TextObject
{
public:
    TextObject();
    ~TextObject();
    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
        YELLOW_TEXT = 3,
    };
    bool LoadFromRenderText(SDL_Renderer* renderer, TTF_Font* font);
    void SetColor(int type);
    void RenderText(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetText(const std::string& text) {str_val = text;}
    void Free();

private:
    std::string str_val;
    SDL_Color text_color{};
    SDL_Texture* texture;
    int width{};
    int height{};
};

#endif //UNDEFINED_GAME_TEXTOBJECT_H
