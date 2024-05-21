#include "Shinchan.h"

Shin::Shin() {
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_speed = 0;
    y_speed = 0;
    width_frame = 0;
    height_frame = 0;
    Shin_state = -1;
    input_type = {0,0,0,0};
    on_ground = false;
    has_attacked = false;
    being_hit = false;
    map_x_ = 0;
    map_y_ = 0;
    star_count = 0;
    hp = 0;
    die = false;
}

Shin::~Shin() = default;

bool Shin::LoadImg(const char * path, SDL_Renderer* renderer) {
    bool ret = BaseObject::LoadImg(path, renderer);

    if(ret)
    {
        width_frame = rect.w / FRAMES;
        height_frame = rect.h - 6;
    }
    else
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    }
    return ret;
}

SDL_Rect Shin::get_Shin_frame() {
    return {rect.x, rect.y, width_frame, height_frame};
}

void Shin::set_clips() {
    if(width_frame > 0 && height_frame > 0)
    {
        for(int i = 0; i < FRAMES; i++)
        {
            frame_clip[i].x = i*width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void Shin::UpdateFrame(SDL_Renderer* renderer) {
    UpdateState(renderer);

    if (input_type.left == 1 || input_type.right == 1 || input_type.attack == 1) {
        frame = (frame + 1) % 9;
    }
    else
    {
        frame = 0;
        UpdateState(renderer);
    }

    rect.x = (int)x_pos - map_x_;
    rect.y = (int)y_pos - map_y_;

    SDL_Rect* current_clip = &frame_clip[frame];
    SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};
    SDL_RenderCopy(renderer, p_object, current_clip, &renderQuad);
}

void Shin::UpdateState(SDL_Renderer* renderer) {
    if (on_ground) {
        UpdateGroundState(renderer);
    } else {
        UpdateJumpState(renderer);
    }
}

void Shin::UpdateGroundState(SDL_Renderer* renderer) {
    if (Shin_state == HIT_LEFT || Shin_state == HIT_RIGHT) {
        HandleHitState(renderer);
    } else if (input_type.attack == 1) {
        HandleAttackState(renderer);
    } else {
        HandleMoveState(renderer);
    }
}

void Shin::UpdateJumpState(SDL_Renderer* renderer) {
    if (Shin_state == RUN_RIGHT) {
        LoadImg("image/jump_right.png", renderer);
    } else if (Shin_state == RUN_LEFT) {
        LoadImg("image/jump_left.png", renderer);
    }
}

void Shin::HandleMoveState(SDL_Renderer* renderer) {
    if (input_type.right == 1) {
        LoadImg("image/run_right.png", renderer);
    } else if (input_type.left == 1) {
        LoadImg("image/run_left.png", renderer);
    } else if (Shin_state == RUN_LEFT) {
        LoadImg("image/left.png", renderer);
    } else {
        LoadImg("image/right.png", renderer);
    }
}

void Shin::HandleAttackState(SDL_Renderer* renderer) {
    if (Shin_state == RUN_RIGHT) {
        LoadImg("image/attack_right.png", renderer);
    } else if (Shin_state == RUN_LEFT) {
        LoadImg("image/attack_left.png", renderer);
    }
}

void Shin::HandleHitState(SDL_Renderer* renderer) {
    if (SDL_GetTicks() - lastHitTime >= HIT_TIME) {
        being_hit = false;
        Shin_state = (Shin_state == HIT_LEFT) ? RUN_LEFT : RUN_RIGHT;
        LoadImg((Shin_state == RUN_LEFT) ? "image/left.png" : "image/right.png", renderer);
    } else {
        input_type = {0,0,0,0};
        being_hit = true;
        x_pos += (Shin_state == HIT_LEFT) ? REPEL_DISTANCE : -REPEL_DISTANCE;
        LoadImg((Shin_state == HIT_LEFT) ? "image/hit_left.png" : "image/hit_right.png", renderer);
    }
}

void Shin::HandleAttack(SDL_Renderer* renderer) {
    if (!has_attacked) {
        if (on_ground && input_type.right != 1 && input_type.left != 1) {
            input_type.attack = 1;
            auto *p_baseball = new Baseball();
            p_baseball->LoadImg("image/baseball.png", renderer);

            if (Shin_state == RUN_RIGHT) {
                p_baseball->set_baseball_dir(Baseball::DIR_RIGHT);
                p_baseball->SetRect(rect.x + width_frame - 30, rect.y + height_frame * 0.4);
            } else if (Shin_state == RUN_LEFT) {
                p_baseball->set_baseball_dir(Baseball::DIR_LEFT);
                p_baseball->SetRect(rect.x, rect.y + height_frame * 0.4);
            }

            p_baseball->set_x_val(30);
            p_baseball->set_is_move(true);

            p_baseball_list.push_back(p_baseball);
            has_attacked = true;
        }
    }
}

void Shin::HandleKeyDown(SDL_Renderer* renderer, SDL_Keycode key) {
    switch (key) {
        case SDLK_d:
        case SDLK_RIGHT:
            Shin_state = RUN_RIGHT;
            input_type.right = 1;
            input_type.left = 0;
            UpdateState(renderer);
            break;
        case SDLK_a:
        case SDLK_LEFT:
            Shin_state = RUN_LEFT;
            input_type.left = 1;
            input_type.right = 0;
            UpdateState(renderer);
            break;
        case SDLK_w:
        case SDLK_UP:
            input_type.jump = 1;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            if (!has_attacked) {
                HandleAttack(renderer);
            }
            break;
        default:
            break;
    }
}

void Shin::HandleKeyUp(SDL_Keycode key) {
    switch (key) {
        case SDLK_d:
        case SDLK_RIGHT:
            input_type.right = 0;
            break;
        case SDLK_a:
        case SDLK_LEFT:
            input_type.left = 0;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            input_type.attack = 0;
            break;
        default:
            break;
    }
}

void Shin::HandleInput(SDL_Renderer* renderer, SDL_Event events) {
    if (!being_hit) {
        if (events.type == SDL_KEYDOWN) {
            HandleKeyDown(renderer, events.key.keysym.sym);
        } else if (events.type == SDL_KEYUP) {
            HandleKeyUp(events.key.keysym.sym);
        }
    }
}

void Shin::RemoveBaseball(const int &idx) {
    int size = (int)p_baseball_list.size();
    if(size > 0 && idx < size)
    {
        Baseball* p_baseball = p_baseball_list[idx];
        p_baseball_list.erase(p_baseball_list.begin() + idx);
        if(p_baseball)
        {
            p_baseball = nullptr;
            delete p_baseball;
            has_attacked = false;
        }
    }
}

void Shin::HandleBaseball(SDL_Renderer* renderer, Mix_Chunk* throw_s)
{
    for(int i = 0; i < p_baseball_list.size(); i++)
    {
        Baseball *p_baseball = p_baseball_list[i];
        {
            if (p_baseball != nullptr && has_attacked) {
                if (p_baseball->get_is_move()) {
                    Mix_PlayChannel(-1, throw_s,0);
                    int distance = (int)x_pos - map_x_ + 315;
                    p_baseball->HandleMove(distance);
                    p_baseball->Render(renderer);
                } else {
                    p_baseball_list.erase(p_baseball_list.begin() + i);
                    p_baseball = nullptr;
                    delete p_baseball;
                    has_attacked = false;
                }
            }
        }
    }
}

void Shin::Action(Map &map_data, Mix_Chunk* star_s) {
    if(!has_attacked)
    {
        x_speed = 0;
        y_speed += GRAVITY_SPEED;

        if(y_speed >= MAX_FALL_SPEED)
        {
            y_speed = MAX_FALL_SPEED;
        }
        if(input_type.left == 1)
        {
            x_speed -= SHIN_SPEED;
        }
        else if(input_type.right == 1)
        {
            x_speed += SHIN_SPEED;
        }
        if(input_type.jump == 1)
        {
            if(on_ground)
            {
                y_speed = - SHIN_JUMP;
            }
            on_ground = false;
            input_type.jump = 0;
        }

        CheckCollision(map_data, star_s);
        CenterOnShin(map_data);
    }
}

void Shin::CenterOnShin(Map &map_data) const {
    map_data.start_x = (int) x_pos - (SCREEN_WIDTH/2) + 140;
    if(map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if(map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }

    map_data.start_y = (int)y_pos - (SCREEN_HEIGHT/6);
    if(map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if(map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
    {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}

bool Shin::isEmptyTile(int value) {
    return std::find(checkValues.begin(), checkValues.end(), value) != checkValues.end();
}

void Shin::CheckCollision(Map &map_data, Mix_Chunk* star_sound) {
    // Check horizontal
    CheckHorizontalCollision(map_data, star_sound);

    // Check vertical
    CheckVerticalCollision(map_data, star_sound);

    // Update position
    x_pos += x_speed;
    y_pos += y_speed;

    if (x_pos < 0) {
        x_pos = 0;
    } else if ((int)x_pos + width_frame > map_data.max_x) {
        x_pos = (float)map_data.max_x - (float)width_frame - 1;
    }

    if (y_pos > (float)map_data.max_y || get_Shin_hp() <= 0) {
        die = true;
    }
}

void Shin::CheckHorizontalCollision(Map &map_data, Mix_Chunk* star_sound) {
    int x1 = (int)(x_pos + x_speed) / TILE_SIZE;
    int x2 = ((int)x_pos + (int)x_speed + width_frame) / TILE_SIZE;
    int y1 = (int)y_pos / TILE_SIZE;
    int y2 = ((int)y_pos + height_frame) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (x_speed > 0) { // Move right
            CheckTileCollision(map_data, star_sound, y1, x2, y2, x2, &x_pos, x1, false);
        } else if (x_speed < 0) { // Move left
            CheckTileCollision(map_data, star_sound, y1, x1, y2, x1, &x_pos, x1 + 1, false);
        }
    }
}

void Shin::CheckVerticalCollision(Map &map_data, Mix_Chunk* star_sound) {
    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    int x1 = ((int)x_pos + 20) / TILE_SIZE;
    int x2 = ((int)x_pos + width_min) / TILE_SIZE;
    int y1 = (int)(y_pos + y_speed) / TILE_SIZE;
    int y2 = ((int)y_pos + (int)y_speed + height_frame - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (y_speed > 0) { // Fall
            CheckTileCollision(map_data, star_sound, y2, x1, y2, x2, &y_pos, y2, true);
        } else if (y_speed < 0) { // Jump
            CheckTileCollision(map_data, star_sound, y1, x1, y1, x2, &y_pos, y1 + 1, true);
        }
    }
}

void Shin::CheckTileCollision(Map &map_data, Mix_Chunk* star_sound, int y1, int x1, int y2, int x2, float* pos, int reset_pos, bool vertical) {
    int tile1 = map_data.tiles[y1][x1];
    int tile2 = map_data.tiles[y2][x2];

    if (tile1 == STAR) {
        Mix_PlayChannel(-1, star_sound, 0);
        map_data.tiles[y1][x1] = BLANK_TILE;
        Count_star();
    } else if (tile2 == STAR) {
        Mix_PlayChannel(-1, star_sound, 0);
        map_data.tiles[y2][x2] = BLANK_TILE;
        Count_star();
    } else if (!isEmptyTile(tile1) || !isEmptyTile(tile2)) {
        if (vertical) {
            if(y_speed > 0)
            {
                *pos = (float) y2 * TILE_SIZE;
                *pos -= (float)(height_frame + 1);
                y_speed = 0;
                on_ground = true;
            }
            else
            {
                *pos = (float) (y1 + 1) * TILE_SIZE;
                y_speed = 0;
            }
        }
        else {
            *pos = (float)reset_pos * TILE_SIZE;
            x_speed = 0;
        }
    }
}

void Shin::RenderHealthBar(SDL_Renderer* renderer) const {
    int barWidth = hp;
    int barHeight = 8;
    int barX = 115;
    int barY = 60;

    // Draw grey background healthBar
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // grey
    SDL_Rect backgroundRect = {barX, barY, 100, barHeight};
    SDL_RenderFillRect(renderer, &backgroundRect);

    // draw black outline healthBar
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
    SDL_Rect outlineRect = {barX - 2, barY - 2, 104, barHeight + 4};
    SDL_RenderDrawRect(renderer, &outlineRect);

    // draw white outline healthBar
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_Rect inlineRect = {barX - 1, barY - 1, 102, barHeight + 2};
    SDL_RenderDrawRect(renderer, &inlineRect);

    // Draw healthBar
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
    SDL_Rect healthBar = {barX, barY, barWidth, barHeight};
    SDL_RenderFillRect(renderer, &healthBar);
}

void Shin::Count_star() {
    star_count++;
}
