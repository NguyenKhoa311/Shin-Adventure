//
// Created by Hoang Nguyen on 22/03/2024.
//

#ifndef UNDEFINED_GAME_GAME_H
#define UNDEFINED_GAME_GAME_H


#define INITIAL_SPEED 5

struct Character {
    int x, y;
    int dx = 0, dy = 0;
//    int ay = -10;
    int speed = INITIAL_SPEED;
//    Graphics graphics;

    void jump_forward(){
        x += 50;
    }

    void jump_backward(){
        x -= 50;
    }

    void jump()
    {
        y -= 30;
    }

    void drop()
    {
        if(y == 300) y += 0;
        else y += 30;
    }

    void move() {
        x += dx;
        y += dy;
    }
    void Up() {
        dy = -speed;
        dx = 0;
    }
    void Down(){
        if (y == 300) dy = 0 ;
        else {
            dy = speed;
            dx = 0;
        }
    }
    void Left() {
        dy = 0;
        dx = -speed;
    }
    void Right() {
        dy = 0;
        dx = speed;
    }
};

bool gameOver(const Character& character) {
    return character.x < -20 || character.x >= SCREEN_WIDTH + 20 ||
           character.y < -200 || character.y >= SCREEN_HEIGHT - 67;
}


#endif //UNDEFINED_GAME_GAME_H
