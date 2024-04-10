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
    TileMat() {;}
    ~TileMat() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(const char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    void SetMap(Map& map_data) {game_map_ = map_data;};
    Map getMap() const {return game_map_;}

private:
    Map game_map_;
    TileMat tile_mat[MAX_TILE];
};

#endif //UNDEFINED_GAME_GAME_MAP_H
