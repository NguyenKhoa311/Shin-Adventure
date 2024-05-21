#include "game_map.h"

void GameMap::LoadMap(const char *name)
{
    std::ifstream map(name);
    if(!map)
    {
        std::cout << "Khong the mo tep";
    }

    for(auto &tile : game_map.tiles)
    {
        for(int &j : tile)
        {
            int num;
            map >> num;
            j = num;
        }
    }

    game_map.max_x = MAX_MAP_X * TILE_SIZE;
    game_map.max_y = MAX_MAP_Y * TILE_SIZE;
    game_map.start_x = 0;
    game_map.start_y = 0;

    map.close();
}

void GameMap::LoadTiles(SDL_Renderer* renderer) {
    std::ifstream tiles;
    for(int i = 0; i < MAX_TILE; i++)
    {
        std::string file_img = "image/" + std::to_string(i) + ".png";
        tiles.open(file_img);
        if (!tiles) {
            continue;
        }
        tiles.close();
        tile_list[i].LoadImg(file_img.c_str(), renderer);
    }
}

void GameMap::DrawMap(SDL_Renderer* renderer) {
    int tile_x;
    int x1 = (game_map.start_x % TILE_SIZE)*-1;
    int x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    int tile_y = game_map.start_y / TILE_SIZE;
    int y1 = (game_map.start_y % TILE_SIZE)*-1;
    int y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for(int i = y1; i < y2; i += TILE_SIZE)
    {
        tile_x = game_map.start_x / TILE_SIZE;
        for(int j = x1; j < x2; j += TILE_SIZE)
        {
            int tile = game_map.tiles[tile_y][tile_x];
            if(tile > 0 && tile < MAX_TILE)
            {
                tile_list[tile].SetRect(j,i);
                tile_list[tile].Render(renderer);
            }
            tile_x++;
        }
        tile_y++;
    }
}

