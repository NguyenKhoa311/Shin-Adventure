#include "Menu.h"

const std::string gOver = "GAME OVER!!!";
const std::string gWin = "YOU WIN !!!";

Menu::Menu() = default;

Menu::~Menu() {
    menu.Free();
    end_menu.Free();
    instruction.Free();
    play.Free();
    exit.Free();
    backButton.Free();
    playAgain.Free();
    Mix_FreeChunk(button_sound);
    Mix_FreeChunk(choose);
    Mix_FreeMusic(menu_ms);
}

void Menu::SetUp(SDL_Renderer* renderer) {
    menu.LoadImg("image/main_menu.png", renderer);
    instruction.LoadImg("image/info.png", renderer);
    play.LoadImg("image/play.png", renderer);
    exit.LoadImg("image/exit.png", renderer);
    menu_ms = Mix_LoadMUS("sounds/menu.mp3");
    button_sound = Mix_LoadWAV("sounds/button.wav");
    choose = Mix_LoadWAV("sounds/choose.mp3");
    SetPos(pos[PLAY], 75, 250, 250, 100); // 0
    SetPos(pos[EXIT], 75, 400, 250, 100); // 1
    SetPos(pos[INFO], 900, 550, 100, 100); // 2
}

bool Menu::LoadImg(const char *path, SDL_Renderer *renderer) {
    return BaseObject::LoadImg(path, renderer);
}

void Menu::SetPos(SDL_Rect &button, const int &x, const int &y, const int &w, const int &h) {
    BaseObject::SetPos(button, x, y, w, h);
}

bool Menu::CheckFocusWithButton(const int& x, const int& y, const SDL_Rect& rect) {
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

int Menu::ShowMenu(SDL_Renderer* renderer) {
    SetPos(src[PLAY], 0, 0, 250, 100);
    SetPos(src[EXIT], 0, 0, 250, 100);
    SetPos(src[INFO], 0, 0, 100, 100);
    Mix_PlayMusic(menu_ms,-1);

    while (true) {
        SDL_RenderClear(renderer);
        menu.Render(renderer, 0, 0);
        play.Render(renderer, &src[PLAY], &pos[PLAY]);
        exit.Render(renderer, &src[EXIT], &pos[EXIT]);
        instruction.Render(renderer, &src[INFO], &pos[INFO]);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&m_event)) {
            switch(m_event.type) {
                case SDL_QUIT:
                    menu.Free();
                    instruction.Free();
                    play.Free();
                    exit.Free();
                    return 1;
                case SDL_MOUSEMOTION:
                    x_m = m_event.motion.x;
                    y_m = m_event.motion.y;
                    if (CheckFocusWithButton(x_m, y_m, pos[PLAY])) {
                        if (!selected[PLAY]) {
                            Mix_PlayChannel(-1,button_sound,0);
                            selected[PLAY] = true;
                            SetPos(src[PLAY], 250, 0, 250, 100);
                        }
                    }
                    else {
                        if (selected[PLAY]) {
                            selected[PLAY] = false;
                            SetPos(src[0], 0, 0, 250, 100);
                        }
                    }

                    if (CheckFocusWithButton(x_m, y_m, pos[EXIT])) {
                        if (!selected[EXIT]) {
                            Mix_PlayChannel(-1,button_sound,0);
                            selected[EXIT] = true;
                            SetPos(src[EXIT], 250, 0, 250, 100);
                        }
                    }
                    else {
                        if (selected[EXIT]) {
                            selected[EXIT] = false;
                            SetPos(src[EXIT], 0, 0, 250, 100);
                        }
                    }


                    if (CheckFocusWithButton(x_m, y_m, pos[INFO])) {
                        if (!selected[INFO]) {
                            Mix_PlayChannel(-1,button_sound,0);
                            selected[INFO] = true;
                            SetPos(src[INFO], 100, 0, 100, 100);
                        }
                    }
                    else {
                        if (selected[INFO]) {
                            selected[INFO] = false;
                            SetPos(src[INFO], 0, 0, 100, 100);
                        }
                    }

                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x_m = m_event.button.x;
                    y_m = m_event.button.y;
                    if (CheckFocusWithButton(x_m, y_m, pos[PLAY])) {
                        Mix_PlayChannel(-1,choose,0);
                        Mix_PauseMusic();
                        return 0;
                    }
                    if (CheckFocusWithButton(x_m, y_m, pos[EXIT])) {
                        Mix_PlayChannel(-1,choose,0);
                        return 1;
                    }
                    if (CheckFocusWithButton(x_m, y_m, pos[INFO])) {
                        Mix_PlayChannel(-1,choose,0);
                        return 2;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                        return 1;
                    }
                default:
                    break;
            }
        }
    }
//    return 1;
}

int Menu::endMenu(SDL_Renderer* renderer) {
    TTF_Font* game_font = TTF_OpenFont("font/Questrian2.ttf", 100);
    gameOver.SetColor(TextObject::RED_TEXT);
    gameOver.SetText(gOver);
    gameOver.LoadFromRenderText(renderer, game_font);
    win.SetColor(TextObject::YELLOW_TEXT);
    win.SetText(gWin);
    win.LoadFromRenderText(renderer, game_font);
    Time.SetColor(TextObject::YELLOW_TEXT);
    SetPos(pos_end[RESTART], 390, 500, 250, 100);
    SetPos(pos_end[EXIT], 690, 500, 250, 100);
    SetPos(pos_end[BACK], 90, 500, 250, 100);
    SetPos(src_end[RESTART], 0, 0, 250, 100);
    SetPos(src_end[EXIT], 0, 0, 250, 100);
    SetPos(src_end[BACK], 0, 0, 250, 100);
    end_menu.LoadImg("image/end_menu.png", renderer);
    backButton.LoadImg("image/back.png", renderer);
    playAgain.LoadImg("image/restart.png", renderer);
    end_exit.LoadImg("image/quit.png", renderer);
    while (true) {
        SDL_RenderClear(renderer);
        end_menu.Render(renderer, 0,0);
        playAgain.Render(renderer, &src_end[RESTART] , &pos_end[RESTART]);
        end_exit.Render(renderer, &src_end[EXIT], &pos_end[EXIT]);
        backButton.Render(renderer, &src_end[BACK], &pos_end[BACK]);
        if(Game::GameOver)
        {
            gameOver.RenderText(renderer, 260,200);
        }
        else
        {
            Time.SetText(Game::getTime());
            Time.LoadFromRenderText(renderer, game_font);
            Time.RenderText(renderer, 300,200);
            win.RenderText(renderer, 300,100);
        }
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&m_event)) {
            switch(m_event.type) {
                case SDL_QUIT:
                    return 1;
                case SDL_MOUSEMOTION:
                    x_m = m_event.motion.x;
                    y_m = m_event.motion.y;

                    for (int i = 0; i <= 1; i++) {
                        if (CheckFocusWithButton(x_m, y_m, pos_end[i])) {
                            if (!selected_end[i]) {
                                Mix_PlayChannel(-1,button_sound,0);
                                selected_end[i] = true;
                                SetPos(src_end[i], 250, 0,250, 100);
                            }
                        }
                        else {
                            if (selected_end[i]) {
                                selected_end[i] = false;
                                SetPos(src_end[i], 0, 0,250, 100);
                            }
                        }
                    }
                    if (CheckFocusWithButton(x_m, y_m, pos_end[BACK])) {
                        if (!selected_end[BACK]) {
                            Mix_PlayChannel(-1,button_sound,0);
                            selected_end[BACK] = true;
                            SetPos(src_end[BACK], 250, 0,250, 100);
                        }
                    }
                    else {
                        if (selected_end[BACK]) {
                            selected_end[BACK] = false;
                            SetPos(src_end[BACK], 0, 0,250, 100);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x_m = m_event.button.x;
                    y_m = m_event.button.y;

                    for (int i = 0; i <= 1; i++) {
                        if (CheckFocusWithButton(x_m, y_m, pos_end[i])) {
                            Mix_PlayChannel(-1,choose,0);
                            return i;
                        }
                    }
                    if (CheckFocusWithButton(x_m, y_m, pos_end[BACK])) {
                        Mix_PlayChannel(-1,choose,0);
                        return 2;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                        return 1;
                    }
                default:
                    break;
            }
        }
    }
//    return 1;
}

void Menu::FreeEndMenu()
{
    end_exit.Free();
    backButton.Free();
    playAgain.Free();
    gameOver.Free();
    win.Free();
}
