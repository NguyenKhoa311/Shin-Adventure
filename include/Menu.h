#ifndef UNDEFINED_GAME_MENU_H
#define UNDEFINED_GAME_MENU_H

#include "common_game_defs.h"
#include "BaseObject.h"
#include "TextObject.h"
#include "Game.h"

class Menu : public BaseObject
{
public:
    Menu();
    ~Menu();
    void SetUp(SDL_Renderer* renderer);
    bool LoadImg(const char * path, SDL_Renderer* renderer) override;
    void SetPos(SDL_Rect &button, const int &x, const int &y, const int &w, const int &h) override;
    [[nodiscard]] SDL_Texture* GetObject() const override {return p_object;}
    static bool CheckFocusWithButton(const int& x, const int& y, const SDL_Rect& rect);
    int ShowMenu(SDL_Renderer* renderer);
    int endMenu(SDL_Renderer* renderer);
    void FreeEndMenu();
private:
    SDL_Rect pos[MENU_ITEM]{};
    SDL_Rect src[MENU_ITEM]{};
    bool selected[MENU_ITEM] = {false, false, false};
    //MENU: 0: play game, 1: exit, 2: info;

    SDL_Rect pos_end[MENU_ITEM]{};
    SDL_Rect src_end[MENU_ITEM]{};
    bool selected_end[MENU_ITEM] = {false, false, false};

    //END: 0: play gain, 1: exit, 2: back

    BaseObject menu;
    BaseObject end_menu;
    BaseObject instruction;
    BaseObject play;
    BaseObject exit;
    BaseObject end_exit;
    BaseObject playAgain;
    BaseObject backButton;
    TextObject gameOver;
    TextObject win;
    TextObject Time;

    SDL_Event m_event{};
    int x_m = 0, y_m = 0;


};

#endif //UNDEFINED_GAME_MENU_H
