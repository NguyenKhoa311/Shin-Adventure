//
// Created by Hoang Nguyen on 29/03/2024.
//
#include "BaseObject.h"
BaseObject::BaseObject() {
    p_object = nullptr;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(const char* path, SDL_Renderer* renderer) {
    Free();
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", path);
    SDL_Texture * new_texture = nullptr;

    SDL_Surface* load_surface = IMG_Load(path);
    if(load_surface != nullptr)
    {
        new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
        if(new_texture != nullptr)
        {
            rect.w = load_surface->w;
            rect.h = load_surface->h;
        }
        else {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
        }
        SDL_FreeSurface(load_surface);
    }
    p_object = new_texture;
    return p_object != nullptr;
}

void BaseObject::SetPos(SDL_Rect &button, const int &x, const int &y, const int &w, const int &h) {
    button.x = x;
    button.y = y;
    button.w = w;
    button.h = h;
}

void BaseObject::Render(SDL_Renderer* renderer, const SDL_Rect *clip) {
    SDL_Rect renderquad = {rect.x, rect.y ,rect.w ,rect.h};

    SDL_RenderCopy(renderer, p_object, clip, &renderquad);
}

void BaseObject::Render(SDL_Renderer* renderer, int x, int y, int width, int height, const SDL_Rect *clip) {
    SDL_Rect renderquad = {x, y, width, height};

    SDL_RenderCopy(renderer, p_object, clip, &renderquad);
}

void BaseObject::Render(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect destRect = { x, y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, p_object, nullptr, &destRect);
}

void BaseObject::Render(SDL_Renderer *renderer, const SDL_Rect *src, const SDL_Rect *dst) {
    SDL_RenderCopy(renderer, p_object, src, dst);
}

void BaseObject::Free() {
    if(p_object != nullptr)
    {
        SDL_DestroyTexture(p_object);
        p_object = nullptr;
        rect.w = 0;
        rect.h = 0;
    }
}

