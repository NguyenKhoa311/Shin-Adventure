//
// Created by Hoang Nguyen on 27/03/2024.
//

#ifndef UNDEFINED_GAME_GAME_MAP_H
#define UNDEFINED_GAME_GAME_MAP_H
#include "common_game_defs.h"
#include "BaseObject.h"


class TileMat : public BaseObject
{
public:
    TileMat() = default;
    ~TileMat() = default;
};

class GameMap
{
public:
    GameMap() = default;
    ~GameMap() = default;

    void LoadMap(const char* name);
    void LoadTiles(SDL_Renderer* renderer);
    void DrawMap(SDL_Renderer* renderer);
    void SetMap(Map& map_data) {game_map = map_data;};
    [[nodiscard]] Map getMap() const {return game_map;}

private:
    Map game_map{};
    TileMat tile_list[MAX_TILE];
};

#endif //UNDEFINED_GAME_GAME_MAP_H
