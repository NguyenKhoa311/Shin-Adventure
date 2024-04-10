//
// Created by Hoang Nguyen on 27/03/2024.
//
#include "game_map.h"

void GameMap::LoadMap(const char *name)
{
    FILE* fp = nullptr;
    fp = fopen(name, "r");
    if(fp == nullptr)
    {
        std::cout << "Khong the mo tep";
    }
    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;
    for(int i = 0; i < MAX_MAP_Y; i++)
    {
        for(int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf(fp, "%d", &game_map_.tile[i][j]);
            int val = game_map_.tile[i][j];
            if(val > 0 && val < MAX_TILE)
            {
                if(j > game_map_.max_x_)
                {
                    game_map_.max_x_ = j;
                }

                if(i > game_map_.max_y_)
                {
                    game_map_.max_y_ = i;
                }
            }
        }
    }

    game_map_.max_x_ = (game_map_.max_x_ + 1)*TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1)*TILE_SIZE;
    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    game_map_.file_name_ = name;
    fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer *screen) {
    char file_img[70];
    FILE *fp = nullptr;

    for(int i = 0; i < MAX_TILE; i++)
    {
        snprintf(file_img,sizeof(file_img), "image/%d.png", i);

        fp = fopen(file_img, "r");
        if(fp == nullptr)
        {
            continue;
        }
        fclose(fp);

        tile_mat[i].LoadImg(file_img, screen);
    }
}

void GameMap::DrawMap(SDL_Renderer *screen) {
    int map_x;
    int x1 = (game_map_.start_x_ % TILE_SIZE)*-1;
    int x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    int map_y = game_map_.start_y_ / TILE_SIZE;
    int y1 = (game_map_.start_y_ % TILE_SIZE)*-1;
    int y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for(int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.start_x_ / TILE_SIZE;
        for(int j = x1; j < x2; j += TILE_SIZE)
        {
            int val = game_map_.tile[map_y][map_x];
            if(val > 0 && val < MAX_TILE)
            {
                tile_mat[val].SetRect(j,i);
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}

