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

bool BaseObject::LoadImg(const char * path, SDL_Renderer *screen) {
    Free();
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", path);
    SDL_Texture * new_texture = nullptr;

    SDL_Surface* load_surface = IMG_Load(path);
    if(load_surface != nullptr)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
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

void BaseObject::Render(SDL_Renderer *des, const SDL_Rect *clip) {
    SDL_Rect renderquad = {rect.x, rect.y ,rect.w ,rect.h};

    SDL_RenderCopy(des, p_object, clip, &renderquad);
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