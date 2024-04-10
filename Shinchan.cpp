//
// Created by Hoang Nguyen on 28/03/2024.
//
#include "Shinchan.h"

Shin::Shin() {
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status = -1;
    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    input_type.attack = 0;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;
    comeback_time = 0;
    star_count = 0;
}

Shin::~Shin() = default;

bool Shin::LoadImg(const char * path, SDL_Renderer *screen) {
    bool ret = BaseObject::LoadImg(path ,screen);

    if(ret)
    {
        width_frame = rect.w/10;
        height_frame = rect.h - 6;
    }
    else
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    }
    return ret;
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

void Shin::Show(SDL_Renderer *des) {
    UpdatePlayer(des);

    if (input_type.left == 1 || input_type.right == 1 || input_type.attack == 1) {
        frame++;
    }
    else
    {
        frame = 0;
        UpdatePlayer(des);
    }

    if(frame >= 9)
    {
        frame = 0;
    }

    if(comeback_time == 0)
    {
        rect.x = (int)x_pos - map_x_;
        rect.y = (int)y_pos - map_y_;

        SDL_Rect* current_clip = &frame_clip[frame];

        SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};

        SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
    }
}

void Shin::UpdatePlayer(SDL_Renderer *des) {
    if(on_ground)
    {
        if(input_type.right == 1)
        {
            LoadImg("image/run_right.png", des);
        }
        else if(input_type.left == 1)
        {
            LoadImg("image/run_left.png", des);
        }
        else if(input_type.attack == 1 && status == WALK_RIGHT)
        {
            LoadImg("image/attack_right.png",des);
        }
        else if(input_type.attack == 1 && status == WALK_LEFT)
        {
            LoadImg("image/attack_left.png",des);
        }
        else if(status == WALK_LEFT)
        {
            LoadImg("image/left.png", des);
        }
        else
        {
            LoadImg("image/right.png", des);
        }
    }
    else
    {
        if(status == WALK_RIGHT)
        {
            LoadImg("image/jump_right.png", des);
        }
        else if(status == WALK_LEFT)
        {
            LoadImg("image/jump_left.png", des);
        }
    }
}

void Shin::HandleInputAction(SDL_Event events, SDL_Renderer *screen) {
    if(events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_d:
            case SDLK_RIGHT:
            {
                status = WALK_RIGHT;
                input_type.right = 1;
                input_type.left = 0;
                UpdatePlayer(screen);
            }
            break;

            case SDLK_a:
            case SDLK_LEFT:
            {
                status = WALK_LEFT;
                input_type.left = 1;
                input_type.right = 0;
                UpdatePlayer(screen);
            }
            break;

            case SDLK_w:
            case SDLK_UP:
            {
                input_type.jump = 1;
            }
            break;

            case SDLK_s:
            case SDLK_DOWN:
            {
                if(on_ground && input_type.right != 1 && input_type.left != 1)
                {
                    input_type.attack = 1;
                    auto* p_baseball = new Baseball();
                    p_baseball->LoadImg("image/baseball.png", screen);
                    if(status == WALK_RIGHT)
                    {
                        p_baseball->set_baseball_dir(Baseball::DIR_RIGHT);
                        p_baseball->SetRect(this->rect.x + width_frame - 20, rect.y + height_frame * 0.4);
                    }
                    else if(status == WALK_LEFT)
                    {
                        p_baseball->set_baseball_dir(Baseball::DIR_LEFT);
                        p_baseball->SetRect(this->rect.x, rect.y + height_frame * 0.4);
                    }

                    p_baseball->set_x_val(30);
                    p_baseball->set_is_move(true);

                    p_baseball_list.push_back(p_baseball);
                }
            }
            break;
        }
    }
    else if(events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_d:
            case SDLK_RIGHT:
            {
                input_type.right = 0;
            }
            break;

            case SDLK_a:
            case SDLK_LEFT:
            {
                input_type.left = 0;
            }
            break;

            case SDLK_s:
            case SDLK_DOWN:
            {
                input_type.attack = 0;
            }
            break;
        }
    }

}

void Shin::HandleBaseball(SDL_Renderer* des)
{
    for(int i = 0; i < p_baseball_list.size(); i++)
    {
        Baseball* p_baseball = p_baseball_list.at(i);
        {
            if(p_baseball != nullptr)
            {
                if(p_baseball->get_is_move())
                {
                    p_baseball->HandleMove(SCREEN_WIDTH);
                    p_baseball->Render(des);
                }
                else
                {
                    p_baseball_list.erase(p_baseball_list.begin() + i);
                    delete p_baseball;
                    p_baseball = nullptr;
                }
            }
        }
    }
}

void Shin::DoPlayer(Map &map_data) {
    if(comeback_time == 0)
    {
        x_val = 0;
        y_val += GRAVITY_SPEED;

        if(y_val >= MAX_FALL_SPEED)
        {
            y_val = MAX_FALL_SPEED;
        }

        if(input_type.left == 1)
        {
            x_val -= SHIN_SPEED;
        }
        else if(input_type.right == 1)
        {
            x_val += SHIN_SPEED;
        }

        if(input_type.jump == 1)
        {
            if(on_ground)
            {
                y_val = - SHIN_JUMP;
            }
            on_ground = false;
            input_type.jump = 0;
        }

        CheckToMap(map_data);
        CenterEntityOnMap(map_data);
    }

    if(comeback_time > 0)
    {
        comeback_time--;
        if(comeback_time == 0)
        {
            on_ground = false;
            status = WALK_RIGHT;
            map_x_ = 0;
            x_pos = 0;
            y_pos = 0;
            x_val = 0;
            y_val = 0;
        }
    }

}

void Shin::CenterEntityOnMap(Map &map_data) const {
    map_data.start_x_ = (int) x_pos - (SCREEN_WIDTH/2);
    if(map_data.start_x_ < 0)
    {
        map_data.start_x_ = 0;
    }
    else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ = (int)y_pos - (SCREEN_HEIGHT/2);
    if(map_data.start_y_ < 0)
    {
        map_data.start_y_ = 0;
    }
    else if(map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
    {
        map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
    }
}

void Shin::CheckToMap(Map &map_data) {

    // check horizontal
    int height_min = height_frame < 2*TILE_SIZE ? height_frame : 2*TILE_SIZE;

    int x1 = (int) (x_pos + x_val) / TILE_SIZE;
    int x2 = ( (int) x_pos + (int) x_val + width_frame - 1) / TILE_SIZE;

    int y1 = (int)y_pos/TILE_SIZE;
    int y2 = ((int)y_pos + height_min - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val > 0) // move right
        {
            int top_right = map_data.tile[y1][x2];
            int bottom_right = map_data.tile[y2][x2];

            if(top_right == STAR)
            {
                map_data.tile[y1][x2] = BLANK_TILE;
                Count_star();
            }
            else if(bottom_right == STAR)
            {
                map_data.tile[y2][x2] = BLANK_TILE;
                Count_star();
            }
            else
            {
                if(top_right != BLANK_TILE || bottom_right != BLANK_TILE)
                {
                    x_pos = (float)x2 * TILE_SIZE;
                    x_pos -= (float)(width_frame - 1);
                    x_val = 0;
                }
            }
        }
        else if(x_val < 0) // move left
        {
            int top_left = map_data.tile[y1][x1];
            int bottom_left = map_data.tile[y2][x1];

            if(top_left == STAR)
            {
                map_data.tile[y1][x1] = BLANK_TILE;
                Count_star();
            }
            else if(bottom_left == STAR)
            {
                map_data.tile[y2][x1] = BLANK_TILE;
                Count_star();
            }
            else
            {
                if(top_left != BLANK_TILE || bottom_left != BLANK_TILE)
                {
                    x_pos = (float)(x1 + 1)*TILE_SIZE;
                    x_val = 0;
                }
            }
        }
    }

    //check vertical

    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = ((int)x_pos + 20)/TILE_SIZE;
    x2 = ((int)x_pos + width_min)/TILE_SIZE;

    y1 = (int) (y_pos + y_val)/TILE_SIZE;
    y2 = ((int) y_pos + (int) y_val + height_frame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_val > 0)
        {
            int bottom_left = map_data.tile[y2][x1];
            int bottom_right = map_data.tile[y2][x2];
            if(bottom_left == STAR)
            {
                map_data.tile[y2][x1] = BLANK_TILE;
                Count_star();
            }
            else if(bottom_right == STAR)
            {
                map_data.tile[y2][x2] = BLANK_TILE;
                Count_star();
            }
            else
            {
                if(bottom_left != BLANK_TILE || bottom_right != BLANK_TILE)
                {
                    y_pos = (float) y2 * TILE_SIZE;
                    y_pos -= (float)(height_frame + 1);
                    y_val = 0;
                    on_ground = true;
                }
            }
        }
        else if(y_val < 0)
        {
            int top_left = map_data.tile[y1][x1];
            int top_right = map_data.tile[y1][x2];
            if(top_left == STAR)
            {
                map_data.tile[y1][x1] = BLANK_TILE;
                Count_star();
            }
            else if(top_right == STAR)
            {
                map_data.tile[y1][x2] = BLANK_TILE;
                Count_star();
            }
            else
            {
                if(top_left != BLANK_TILE || top_right != BLANK_TILE)
                {
                    y_pos = (float) (y1 + 1) * TILE_SIZE;
                    y_val = 0;
                }
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    if(x_pos < 0)
    {
        x_pos = 0;
    }
    else if( (int)x_pos + width_frame > map_data.max_x_)
    {
        x_pos = (float)map_data.max_x_ - (float)width_frame - 1;
    }

    if(y_pos > (float)map_data.max_y_)
    {
        comeback_time = 10;
    }
}

void Shin::Count_star() {
    star_count++;
}