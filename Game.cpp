#include "Game.h"

Game::Game()= default;
Game::~Game() = default;

TTF_Font* font_time = nullptr;
TTF_Font* star_font = nullptr;
TTF_Font* e_font = nullptr;

bool Game::isRunning = false;
bool Game::quit;
bool Game::GameOver;
std::string Game::time;

void Game::logErrorAndExit(const char *msg, const char *error) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
}

bool Game::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        logErrorAndExit("SDL_Init", SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_RenderSetLogicalSize(g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    g_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == nullptr) {
        logErrorAndExit("CreateWindow", SDL_GetError());
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (g_renderer == nullptr) {
        logErrorAndExit("CreateRenderer", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        logErrorAndExit( "SDL_image error:", IMG_GetError());
        return false;
    }

    if(TTF_Init() == -1)
    {
        return false;
    }

    font_time = TTF_OpenFont("font/dlxfont.ttf", 15);
    star_font = TTF_OpenFont("font/Arial Narrow Bold.ttf", 25);
    e_font = TTF_OpenFont("font/Arial Narrow Bold.ttf", 25);
    if(font_time == nullptr || font_time == nullptr || e_font == nullptr)
    {
        return false;
    }

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT,2,4096) == -1)
    {
        return false;
    }

    music = Mix_LoadMUS("sounds/music.wav");
    shin_uoo = Mix_LoadWAV("sounds/shin_uoo.wav");
    hit = Mix_LoadWAV("sounds/hit.wav");
    game_over = Mix_LoadWAV("sounds/game_over.wav");
    punch = Mix_LoadWAV("sounds/punch.wav");
    throw_ball = Mix_LoadWAV("sounds/throw.wav");
    star_sound = Mix_LoadWAV("sounds/star.wav");
    win = Mix_LoadWAV("sounds/victory.mp3");

    if(music == nullptr || shin_uoo == nullptr || game_over == nullptr
    || punch == nullptr || throw_ball == nullptr || star_sound == nullptr
    || hit == nullptr || win == nullptr)
    {
        return false;
    }

    return true;
}

bool Game::LoadResources() {
    if (!background.LoadImg("image/BG.png", g_renderer) ||
        !shin.LoadImg("image/jump_right.png", g_renderer) ||
        !info.LoadImg("image/shin_info.png", g_renderer) ||
        !star_bar.LoadImg("image/star_bar.png", g_renderer) ||
        !enemy_bar.LoadImg("image/enemy_bar.png", g_renderer))
    {
        return false;
    }

    shin.set_clips();
    shin.set_Shin_hp(SHIN_HP);
    zombie.set_enemy_count(0);
    map.LoadMap("map.txt");
    map.LoadTiles(g_renderer);
    exp.LoadImg("image/explosion.png", g_renderer);
    exp.set_clip();
    time_game.SetColor(TextObject::RED_TEXT);
    star.SetColor(TextObject::BLACK_TEXT);
    e_count.SetColor(TextObject::BLACK_TEXT);
    return true;
}

SDL_Renderer* Game::GetRenderer() {
    return g_renderer;
}

void Game::setup() {
    Game::isRunning = true;
    Game::quit = false;
    Game::GameOver = false;
}

void Game::Quit() {

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::FreeObject() {
    Mix_FreeMusic(music);
    Mix_FreeChunk(game_over);
    Mix_FreeChunk(shin_uoo);
    Mix_FreeChunk(punch);
    Mix_FreeChunk(throw_ball);
    Mix_FreeChunk(star_sound);
    Mix_FreeChunk(win);
    Mix_FreeChunk(hit);
    background.Free();
    info.Free();
    star_bar.Free();
    enemy_bar.Free();
    shin.Free();
    zombie.Free();
    time_game.Free();
    star.Free();
    e_count.Free();
}

std::vector<Enemies*> Game::MakeEnemyList()
{
    std::vector<Enemies*> list_enemies;

    auto* moving_enemies = new Enemies[10];
    for(int i = 0; i < 10; i++)
    {
        Enemies* e = (moving_enemies + i);
        if(e != nullptr)
        {
            e->set_input_left(1);
            e->LoadImg("image/zombie_left.png", g_renderer);
            e->Set_clips();
            e->set_move_type(Enemies::MOVE);

            e->set_x_pos((float)1500 + (float)i * 1750);
            e->set_y_pos(0);
            e->set_hp(MOVING_ENEMY_HP);

            float left = e->get_x_pos() - 80;
            float right = e->get_x_pos() + 80;
            e->set_EnemyBor(left, right);

            list_enemies.push_back(e);
        }
    }

    auto* enemies = new Enemies[10];

    for(int i = 0; i < 10; i++)
    {
        Enemies* e = (enemies + i);
        if(e != nullptr)
        {
            e->set_input_left(0);
            e->LoadImg("image/zombie.png", g_renderer);
            e->Set_clips();
            e->set_move_type(Enemies::STATIC);
            e->set_hp(STATIC_ENEMY_HP);
            e->set_x_pos((float)2000 + (float)i * 1500);
            e->set_y_pos(250);

            list_enemies.push_back(e);
        }
    }
    return list_enemies;
}

void Game::RunGameLoop() {
    setup();
    LoadResources();
    std::vector<Enemies*> enemies_list = MakeEnemyList();
    gameStartTime = SDL_GetTicks();
    Mix_PlayChannel(-1,shin_uoo,0);
    Mix_PlayMusic(music,-1);
    while (isRunning) {
        fps_timer.start();
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                isRunning = false;
                quit = true;
            }
            shin.HandleInput(g_renderer,g_event);
        }
        SDL_RenderClear(g_renderer);
        background.Render(g_renderer, 0 ,0);

        Map map_data = map.getMap();

        shin.SetMapXY(map_data.start_x, map_data.start_y);
        shin.Action(map_data, star_sound);
        map.SetMap(map_data);
        map.DrawMap(g_renderer);
        info.Render(g_renderer, 10, 10, 220, 100, nullptr);
        shin.RenderHealthBar(g_renderer);
        star_bar.Render(g_renderer,250, 640, 140, 50, nullptr);
        enemy_bar.Render(g_renderer, 60, 640, 140, 50, nullptr);
        shin.HandleBaseball(g_renderer, throw_ball);
        SDL_Rect sRect = shin.get_Shin_frame();
        for(auto enemy : enemies_list)
        {
            if(enemy != nullptr)
            {
                enemy->SetMapXY(map_data.start_x, map_data.start_y);
                Enemies::renderHealthBar(g_renderer, enemy);
                enemy->ImpMoveType(g_renderer);
                enemy->DoEnemies(map_data);
                enemy->Show(g_renderer);
                SDL_Rect eRect = enemy->get_enemy_frame();
                bool collision = GameDef::CheckCollision(sRect, eRect);
                if(collision)
                {
                    Mix_PlayChannel(-1,hit,0);
                    if(SDL_GetTicks() - shin.get_lastHitTime() >= shin.get_hit_time()) {
                        if(enemy->get_x_pos() < shin.get_x_pos())
                        {
                            shin.set_Shin_state(Shin::HIT_LEFT);
                        }
                        else
                        {
                            shin.set_Shin_state(Shin::HIT_RIGHT);
                        }
                        shin.set_Shin_hp(shin.get_Shin_hp() - ENEMY_DAME);
                        shin.set_lastHitTime(SDL_GetTicks()); // get time Shin being hit
                    }
                }
                if(shin.get_die_state())
                {
                    isRunning = false;
                    Mix_PauseMusic();
                    Mix_VolumeChunk(game_over, MIX_MAX_VOLUME/4);
                    Mix_PlayChannel(-1,game_over,0);
                    GameOver = true;
                }
            }
        }

        int exp_width_frame = exp.get_width_frame();
        int exp_height_frame = exp.get_height_frame();
        std::vector<Baseball*> baseball_list = shin.get_baseball_list();
        for(int i = 0; i < baseball_list.size(); ++i)
        {
            Baseball* p_baseball = baseball_list[i];
            if(p_baseball != nullptr)
            {
                for(int enemy = 0; enemy < enemies_list.size(); ++enemy)
                {
                    Enemies* e = enemies_list[enemy];
                    {
                        if(e != nullptr)
                        {
                            SDL_Rect eRect = e->get_enemy_frame();
                            SDL_Rect bRect = p_baseball->GetRect();

                            bool collision = GameDef::CheckCollision(eRect, bRect);

                            if(collision)
                            {
                                Mix_PlayChannel(-1,punch,0);
                                for(int ex = 0; ex < EXP_FRAME; ex++)
                                {
                                    int x_pos = p_baseball->GetRect().x + exp_width_frame * 0.4 ;
                                    int y_pos = p_baseball->GetRect().y - exp_height_frame * 0.4;

                                    exp.set_frame(ex);
                                    exp.SetRect(x_pos, y_pos);
                                    exp.Show(g_renderer);
                                }
                                e->set_hp(e->get_hp() - SHIN_DAME);
                                shin.RemoveBaseball(i);
                                if(e->get_hp() == 0)
                                {
                                    e->Free();
                                    zombie.set_enemy_count(zombie.get_enemy_count() + 1);
                                    enemies_list.erase(enemies_list.begin() + enemy);
                                }
                            }
                        }
                    }
                }
            }
        }

        shin.UpdateFrame(g_renderer);

        std::string str_time = "Time: ";
        Uint32 time_val = (SDL_GetTicks() - gameStartTime) / 1000;
        Uint32 minutes = time_val / 60;
        Uint32 seconds = time_val % 60;

        std::string str_val = std::to_string(minutes) + ":";
        if (seconds < 10) {
            str_val += "0";
        }
        str_val += std::to_string(seconds);

        str_time += str_val;
        time_game.SetText(str_time);
        time_game.LoadFromRenderText(g_renderer, font_time);
        time_game.RenderText(g_renderer, SCREEN_WIDTH - 150, 15);

        e_count.SetText(std::to_string(zombie.get_enemy_count()));
        e_count.LoadFromRenderText(g_renderer, e_font);
        e_count.RenderText(g_renderer, 130, 653);

        star.SetText(std::to_string(shin.get_star_count()));
        star.LoadFromRenderText(g_renderer, star_font);
        star.RenderText(g_renderer, 320, 653);

        SDL_RenderPresent(g_renderer);
        int present_time = fps_timer.get_ticks();
        if (present_time < TIME_PER_FRAME) {
            SDL_Delay(TIME_PER_FRAME - present_time);
        }

        if(shin.get_star_count() == 80 && zombie.get_enemy_count() == 20) {
            setTime(str_time);
            Mix_PauseMusic();
            Mix_PlayChannel(-1,win,0);
            isRunning = false;
        }
    }
}

