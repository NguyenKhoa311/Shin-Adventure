cmake_minimum_required(VERSION 3.25)
project(undefined_game)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(undefined_game main.cpp common_game_defs.h game_map.h game_map.cpp common_game_defs.cpp Shinchan.h Shinchan.cpp BaseObject.h BaseObject.cpp Timer.h Timer.cpp Baseball.h Baseball.cpp Game.h Game.cpp Enemies.h Enemies.cpp Explosion.h Explosion.cpp TextObject.h TextObject.cpp Menu.h Menu.cpp)
target_link_libraries(undefined_game PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)