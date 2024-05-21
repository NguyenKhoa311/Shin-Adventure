#include "TextObject.h"

TextObject::TextObject() {
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
    texture = nullptr;
}

TextObject::~TextObject() = default;

bool TextObject::LoadFromRenderText(SDL_Renderer* renderer, TTF_Font *font) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
    if(text_surface)
    {
        texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        width = text_surface->w;
        height = text_surface->h;
        SDL_FreeSurface(text_surface);
    }
    return texture != nullptr;
}

void TextObject::SetColor(int type) {
    if(type == RED_TEXT)
    {
        SDL_Color color = {255,0,0};
        text_color = color;
    }
    else if(type == WHITE_TEXT)
    {
        SDL_Color color = {255,255,255};
        text_color = color;
    }
    else if(type == BLACK_TEXT)
    {
        SDL_Color color = {0,0,0};
        text_color = color;
    }
    else if(type == YELLOW_TEXT)
    {
        SDL_Color  color = {255,223,0};
        text_color = color;
    }
}

void TextObject::RenderText(SDL_Renderer* renderer, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center,
                            SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y,width,height};
    if(clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

void TextObject::Free() {
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}
