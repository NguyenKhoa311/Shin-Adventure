//
// Created by Hoang Nguyen on 21/03/2024.
//

#ifndef UNDEFINED_GAME_GRAPHICS_H
#define UNDEFINED_GAME_GRAPHICS_H

#include "common_game_defs.h"
class Graphics {
public:
    Graphics();
    ~Graphics();
    void SetRect (const int& x,const int& y) {rect.x = x, rect.y = y;}
    SDL_Rect GetRect() const {return rect;}
    SDL_Texture* GetTexture() const {return p_object;}
    virtual bool LoadImg(const char* path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();


    void presentIntro(SDL_Texture* texture1, SDL_Texture* texture2);
    void logErrorAndExit(const char* msg, const char* error);
    void init();
    void prepareScene();
    void prepareScene(SDL_Texture * background);
    void presentScene();
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture* texture);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void renderTexture(SDL_Texture *texture, int x, int y, int w, int h);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
    void quit();
protected:
    SDL_Texture* p_object;
    SDL_Rect rect;
};

#endif //UNDEFINED_GAME_GRAPHICS_H
