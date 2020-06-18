#pragma once

#include <ncurses.h>
#include <cmath>
#include "model.hpp"

class Controller
{
private:
    Model * model;
    

public:
    Controller(Model * model)
    {
        this->model = model;
    }

    void keyboard_input()
    {
        keypad(stdscr, TRUE);
        noecho();
        int key = getch();
        switch(key)
        {
            case KEY_LEFT:
                model->dir[0] = 0;
                model->dir[1] = -1;
                break;

            case KEY_RIGHT:
                model->dir[0] = 0;
                model->dir[1] = 1;
                break;

            case KEY_UP:
                model->dir[0] = -1;
                model->dir[1] = 0;
                break;

            case KEY_DOWN:
                model->dir[0] = 1;
                model->dir[1] = 0;
                break;
        }
    }

    void cell_process()
    {
        bool is_growth = false;
        switch(model->map[model->snake_y + model->dir[0]][model->snake_x + model->dir[1]])
        {
            case Cell::BLANK:
                break;

            case Cell::GROWTH:
                is_growth = true;
                model->body_size++;
                model->item_y = -2;
                model->item_x = -2;
                break;

            case Cell::POISON:
                model->body_size--;
                if(model->body_size < 3)
                    game_over();
                model->map[model->body_pos.back().first][model->body_pos.back().second] = Cell::BLANK;
                model->body_pos.pop_back();
                model->item_y = -2;
                model->item_x = -2;
                break;

            case Cell::BODY:
            case Cell::WALL:
            case Cell::IMMUNE_WALL:
                game_over();
                break;
        }

        if(!is_growth) {
            model->map[model->body_pos.back().first][model->body_pos.back().second] = Cell::BLANK;
            model->body_pos.pop_back();
        }
        model->map[model->snake_y][model->snake_x] = Cell::BODY;
        model->body_pos.push_front(std::make_pair(model->snake_y, model->snake_x));

        model->snake_y += model->dir[0];
        model->snake_x += model->dir[1];
        model->map[model->snake_y][model->snake_x] = Cell::HEAD;
    }

    void process_item()
    {
        model->item_tick++;
        if(model->item_y == -1) {
            if(model->item_tick >= model->next_item_tick) {
                do {
                    model->item_y = std::rand() % (MAP_HEIGHT - 2) + 1;
                    model->item_x = std::rand() % (MAP_WIDTH - 2) + 1;
                }
                while(model->map[model->item_y][model->item_x] != Cell::BLANK);

                if(std::rand() % 2 == 0)
                    model->map[model->item_y][model->item_x] = Cell::POISON;
                else
                    model->map[model->item_y][model->item_x] = Cell::GROWTH;

                model->item_tick = 0;
            }
        }
        else if(model->item_tick >= 20 || model->item_y == -2) {
                model->item_tick = 0;
                model->map[model->item_y][model->item_x] = Cell::BLANK;
                model->item_y = -1;
                model->item_x = -1;
                model->next_item_tick = 5 + rand() % 5;
        }
    }

    void game_over()
    {
        model->game_over = true;
    }
};