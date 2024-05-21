#include "Enemies.h"

Enemies::Enemies() {
    hp = 0;
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_velo = 0;
    y_velo = 0;
    width_frame = 0;
    height_frame = 0;
    comeback_time = 0;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;
    border_right = 0;
    border_left = 0;
    input_type.left = 0;
    move_type = STATIC;
    enemy_count = 0;
}

Enemies::~Enemies() = default;

bool Enemies::LoadImg(const char *path, SDL_Renderer* renderer) {
    bool ret = BaseObject::LoadImg(path, renderer);
    if(ret)
    {
        width_frame = rect.w / ENEMY_FRAME;
        height_frame = rect.h - 6;
    }
    else
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    }
    return ret;
}

SDL_Rect Enemies::get_enemy_frame() {
    SDL_Rect eRect;
    eRect.x = rect.x;
    eRect.y = rect.y;
    eRect.w = width_frame;
    eRect.h = height_frame;
    return eRect;
}

void Enemies::Set_clips() {
    if(width_frame > 0 && height_frame > 0)
    {
        for(int i = 0; i < ENEMY_FRAME; i++)
        {
            frame_clip[i].x = i*width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void Enemies::Show(SDL_Renderer *renderer) {
    if(comeback_time == 0)
    {
        rect.x = (int)x_pos - map_x_;
        rect.y = (int)y_pos - map_y_;
        frame++;

        if(frame >= 14)
        {
            frame = 0;
        }

        SDL_Rect* currentCLip = &frame_clip[frame];
        SDL_Rect rendQuad = {rect.x, rect.y, width_frame, height_frame};
        SDL_RenderCopy(renderer, p_object, currentCLip, &rendQuad);
    }
}

void Enemies::DoEnemies(Map& map_data) {
    if(comeback_time == 0)
    {
        x_velo = 0;
        y_velo += ENEMIES_GRAVITY;
        if(y_velo >= MAX_FALL_SPEED)
        {
            y_velo = MAX_FALL_SPEED;
        }

        if(input_type.left == 1)
        {
            x_velo -= ENEMY_SPEED;
        }
        else if(input_type.right == 1)
        {
            x_velo += ENEMY_SPEED;
        }

        CheckCollision(map_data);
    }
    else if(comeback_time > 0)
    {
        comeback_time--;
        if(comeback_time == 0)
        {
            InitEnemies();
        }
    }
}

void Enemies::InitEnemies() {
    if(x_pos > 256)
    {
        x_pos -= 256;
        border_left -= 256;
        border_right -= 256;
    }
    y_pos = 250;
    x_velo = 0;
    y_velo = 0;
    if(get_move_type() == 0) {input_type.left = 0;}
    else input_type.left = 1;
}

void Enemies::CheckCollision(Map& map_data) {
    int x1 = (int) (x_pos + x_velo) / TILE_SIZE;
    int x2 = ( (int) x_pos + (int) x_velo + width_frame) / TILE_SIZE;

    int y1 = (int)y_pos/TILE_SIZE;
    int y2 = ((int)y_pos + height_frame) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_velo > 0) // move right
        {
            int top_right = map_data.tiles[y1][x2];
            int bottom_right = map_data.tiles[y2][x2];

            if( !isEmptyTile(bottom_right) || !isEmptyTile(top_right) )
            {
                x_pos = (float)x1 * TILE_SIZE;
                x_velo = 0;
            }
        }
        else if(x_velo < 0) // move left
        {
            int top_left = map_data.tiles[y1][x1];
            int bottom_left = map_data.tiles[y2][x1];
            if( !isEmptyTile(top_left) || !isEmptyTile(bottom_left) )
            {
                x_pos = (float)(x1 + 1) * TILE_SIZE;
                x_velo = 0;
            }
        }
    }

    //check vertical

    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = ((int)x_pos + 20)/TILE_SIZE;
    x2 = ((int)x_pos + width_min)/TILE_SIZE;

    y1 = (int) (y_pos + y_velo)/TILE_SIZE;
    y2 = ((int) y_pos + (int) y_velo + height_frame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_velo > 0)
        {
            int bottom_left = map_data.tiles[y2][x1];
            int bottom_right = map_data.tiles[y2][x2];

            if(!isEmptyTile(bottom_right) || !isEmptyTile(bottom_left))
            {
                y_pos = (float) y2 * TILE_SIZE;
                y_pos -= (float)(height_frame + 1);
                y_velo = 0;
                on_ground = true;
            }
        }
        else if(y_velo < 0)
        {
            int top_left = map_data.tiles[y1][x1];
            int top_right = map_data.tiles[y1][x2];

            if( !isEmptyTile(top_left) || !isEmptyTile(top_right) )
            {
                y_pos = (float) (y1 + 1) * TILE_SIZE;
                y_velo = 0;
            }
        }
    }

    x_pos += x_velo;
    y_pos += y_velo;

    if(x_pos < 0)
    {
        x_pos = 0;
    }
    else if( (int)x_pos + width_frame > map_data.max_x)
    {
        x_pos = (float)map_data.max_x - (float)width_frame - 1;
    }

    if(y_pos > (float)map_data.max_y)
    {
        comeback_time = 10;
    }
}

bool Enemies::isEmptyTile(int value) {
    return std::find(enemy_checkValues.begin(), enemy_checkValues.end(), value) != enemy_checkValues.end();
}

void Enemies::ImpMoveType(SDL_Renderer* renderer) {
    if(move_type == STATIC){}
    else {
        if(on_ground)
        {
            if(x_pos >= border_right)
            {
                input_type.left = 1;
                input_type.right = 0;
                LoadImg("image/zombie_left.png", renderer);
            }
            else if(x_pos <= border_left)
            {
                input_type.left = 0;
                input_type.right = 1;
                LoadImg("image/zombie_right.png", renderer);
            }
        }
        else
        {
            if(input_type.left == 1)
            {
                LoadImg("image/zombie_left.png", renderer);
            }
        }
    }
}

void Enemies::renderHealthBar(SDL_Renderer* renderer, Enemies* enemy) {
    int currentHealth = enemy->get_enemy_hp();
    int maxHealth;

    if (enemy->get_move_type() == Enemies::MOVE) {
        maxHealth = MOVING_ENEMY_HP;
    } else {
        maxHealth = STATIC_ENEMY_HP;
    }

    float healthRatio = (float)(currentHealth) / (float)maxHealth;
    int healthBarLength = (int)(MAX_HEALTH_BAR_LENGTH * healthRatio);

    SDL_Rect enemyFrame = enemy->get_enemy_frame();
    int healthBarX = enemyFrame.x;
    int healthBarY = enemyFrame.y - 10;
    int healthBarWidth = MAX_HEALTH_BAR_LENGTH;
    int healthBarHeight = 7;

    SDL_Rect healthBarBackground = { healthBarX, healthBarY, healthBarWidth, healthBarHeight };
    SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); // grey
    SDL_RenderFillRect(renderer, &healthBarBackground);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderDrawRect(renderer, &healthBarBackground);

    SDL_Rect healthBar = { healthBarX, healthBarY, healthBarLength - 2, healthBarHeight - 2};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
    SDL_RenderFillRect(renderer, &healthBar);
}
