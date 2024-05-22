cmake_minimum_required(VERSION 3.25)
project(undefined_game)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(undefined_game Shin-Adventure/main.cpp Shin-Adventure/common_game_defs.h Shin-Adventure/game_map.h
        Shin-Adventure/game_map.cpp Shin-Adventure/common_game_defs.cpp Shin-Adventure/Shinchan.h
        Shin-Adventure/Shinchan.cpp Shin-Adventure/BaseObject.h Shin-Adventure/BaseObject.cpp
        Shin-Adventure/Timer.h Shin-Adventure/Timer.cpp Shin-Adventure/Baseball.h
        Shin-Adventure/Baseball.cpp Shin-Adventure/Game.h Shin-Adventure/Game.cpp
        Shin-Adventure/Enemies.h Shin-Adventure/Enemies.cpp Shin-Adventure/Explosion.h
        Shin-Adventure/Explosion.cpp Shin-Adventure/TextObject.h Shin-Adventure/TextObject.cpp
        Shin-Adventure/Menu.h Shin-Adventure/Menu.cpp)
target_link_libraries(undefined_game PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)


#cmake_minimum_required(VERSION 3.25)
#
#set(CMAKE_CXX_STANDARD 17)
#
#project(undefined_game)
#
#add_executable(undefined_game Shin-Adventure/main.cpp Shin-Adventure/common_game_defs.h Shin-Adventure/game_map.h
#        Shin-Adventure/game_map.cpp Shin-Adventure/common_game_defs.cpp Shin-Adventure/Shinchan.h
#        Shin-Adventure/Shinchan.cpp Shin-Adventure/BaseObject.h Shin-Adventure/BaseObject.cpp
#        Shin-Adventure/Timer.h Shin-Adventure/Timer.cpp Shin-Adventure/Baseball.h
#        Shin-Adventure/Baseball.cpp Shin-Adventure/Game.h Shin-Adventure/Game.cpp
#        Shin-Adventure/Enemies.h Shin-Adventure/Enemies.cpp Shin-Adventure/Explosion.h
#        Shin-Adventure/Explosion.cpp Shin-Adventure/TextObject.h Shin-Adventure/TextObject.cpp
#        Shin-Adventure/Menu.h Shin-Adventure/Menu.cpp)
#
## Variables storing SDL framework locations
#set(SDL2
#        /Library/Frameworks/SDL2.framework)
#set(SDL2_image
#        /Library/Frameworks/SDL2_image.framework)
#set(SDL2_ttf
#        /Library/Frameworks/SDL2_ttf.framework)
#set(SDL2_mixer
#        /Library/Frameworks/SDL2_mixer.framework)
#
#target_link_libraries(
#        undefined_game PRIVATE
#        ${SDL2}/Versions/A/SDL2
#        ${SDL2_image}/Versions/A/SDL2_image
#        ${SDL2_ttf}/Versions/A/SDL2_ttf
#        ${SDL2_mixer}/Versions/A/SDL2_mixer
#)
#
#target_include_directories(
#        undefined_game PRIVATE
#        ${SDL2}/Versions/A/Headers
#        ${SDL2_image}/Versions/A/Headers
#        ${SDL2_ttf}/Versions/A/Headers
#        ${SDL2_mixer}/Versions/A/Headers
#)
