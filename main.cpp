//#include "graphics.h"
#include "common_game_defs.h"
#include "BaseObject.h"
#include "game_map.h"
#include "Shinchan.h"
#include "Timer.h"

BaseObject g_background;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(g_window == nullptr)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if(g_screen == nullptr)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(IMG_Init(imgFlags) == true)
            {
                success = false;
            }
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("image/background.jpg", g_screen);
    if(!ret)
    {
        return false;
    }
    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = nullptr;

    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    Timer fps_timer;
    if(!InitData()) return -1;
    if(!LoadBackground()) return -1;

    Shin player;
    player.LoadImg("image/jump_right.png", g_screen);
    player.set_clips();

    GameMap game_map;
    game_map.LoadMap("map.txt");
    game_map.LoadTiles(g_screen);

    bool running = true;
    while (running) {
        fps_timer.start();
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT) running = false;
            player.HandleInputAction(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, nullptr);

        Map map_data = game_map.getMap();

        player.HandleBaseball(g_screen);
        player.SetMapXY(map_data.start_x_, map_data.start_y_);
        player.DoPlayer(map_data);
        player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        SDL_RenderPresent(g_screen);

        int real_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;

        if(real_time < time_one_frame) {
            int delay_time = time_one_frame - real_time;
            if (delay_time >= 0) {
                SDL_Delay(delay_time);
            }
        }
    }

    close();
    return 0;
}
