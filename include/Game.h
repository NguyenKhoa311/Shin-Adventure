#ifndef UNDEFINED_GAME_GAME_H
#define UNDEFINED_GAME_GAME_H

#include "common_game_defs.h"
#include "BaseObject.h"
#include "game_map.h"
#include "Shinchan.h"
#include "Timer.h"
#include "Enemies.h"
#include "Explosion.h"
#include "TextObject.h"

class Game {
public:
    Game();
    ~Game();
    static void logErrorAndExit(const char* msg, const char* error);
    static bool Init();
    bool LoadResources();
    static void Quit();
    void FreeObject();
    void RunGameLoop();
    static std::vector<Enemies*> MakeEnemyList();
    static void setup();
    static bool isRunning;
    static bool GameOver;
    static bool quit;
    static SDL_Renderer* GetRenderer() ;
    static std::string setTime(const std::string& time_) {return time = time_;}
    static std::string getTime() {return time;}

private:
    Explosion exp;
    BaseObject background;
    BaseObject info;
    BaseObject star_bar;
    BaseObject enemy_bar;
    Shin shin;
    Enemies zombie;
    GameMap map;
    Timer fps_timer;
    TextObject time_game;
    TextObject star;
    TextObject e_count;
    Uint32 gameStartTime{};
    static std::string time;
};

#endif //UNDEFINED_GAME_GAME_H
