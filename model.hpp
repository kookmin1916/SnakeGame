#pragma once

#include <deque>
#include <cmath>
#include <algorithm>
#include <ctime>

const int MAP_HEIGHT = 21, MAP_WIDTH = 21;

enum Cell {
    BLANK = 0,
    WALL,
    IMMUNE_WALL,
    HEAD,
    BODY,
    POISON,
    GROWTH
};

class Model
{
public:
    int snake_y = 10, snake_x = 10;
    int body_size = 3;
    int map[MAP_HEIGHT][MAP_WIDTH] = {{0}, };
    int dir[2] = {0, -1};
    int item_tick = 0;
    int next_item_tick;
    int item_y = -1, item_x = -1;
    bool game_over = false;
    bool is_run = false;
    std::deque<std::pair<int, int> > body_pos;

public:
    Model()
    {
        srand(time(NULL));
        next_item_tick = 10 + rand() % 5;

        for(int i = 0; i < MAP_HEIGHT; i++)
            for(int j = 0; j < MAP_WIDTH; j++)
            {
                if((i == 0 || i == MAP_HEIGHT - 1) && (j == 0 || j == MAP_WIDTH - 1))
                    map[i][j] = Cell::IMMUNE_WALL;
                else if(i == 0 || j == 0 || i == MAP_HEIGHT - 1 || j == MAP_WIDTH - 1)
                    map[i][j] = Cell::WALL;
                else
                    map[i][j] = Cell::BLANK;
            }

        map[snake_y][snake_x] = Cell::HEAD;
        for(int i = 1; i <= body_size; i++) 
        {
            map[snake_y][snake_x + i] = Cell::BODY;     
            body_pos.push_back(std::make_pair(snake_y, snake_x + i));
        }

        //map[5][5] = map[3][3] = Cell::GROWTH;
        //map[2][6] = map[4][3] = Cell::POISON;
    }

    bool is_out_of_range(int y, int x)
    {
        return !(y < 0 || x < 0 || y >= MAP_HEIGHT || x >= MAP_WIDTH);
    }
};