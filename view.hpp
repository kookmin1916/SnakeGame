#pragma once

#include <ncurses.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <unistd.h>
#include "model.hpp"
#include "controller.hpp"

const int CELL_WIDTH = 10, CELL_HEIGHT = 10;

class View
{
private:
    Model * model;
    Controller * controller;
    // WINDOW * cells[MAP_WIDTH][MAP_HEIGHT];
    const int COLORS[7] = { 1, 2, 3, 4, 5, 6, 7 };

public:
    View(Model * model, Controller * controller)
    {
        this->model = model;
        this->controller = controller;

        initscr();
        start_color();

        init_pair(1, COLOR_RED, COLOR_WHITE);
        init_pair(2, COLOR_BLACK, COLOR_CYAN);
        init_pair(3, COLOR_BLACK, COLOR_BLUE);
        init_pair(4, COLOR_BLACK, COLOR_RED);
        init_pair(5, COLOR_BLACK, COLOR_YELLOW);
        init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(7, COLOR_BLACK, COLOR_GREEN);

        attron(COLOR_PAIR(1));
        wbkgd(stdscr, COLOR_PAIR(1));
        attroff(COLOR_PAIR(1));

        draw_map();
    }

    void run()
    {
        while(true)
        {
            controller->process_item();
            if(model->game_over)
                break;
            controller->keyboard_input();
            controller->cell_process();
            draw_map();
            refresh();
            // sleep(50);
        }
    }

    void draw_map()
    {
        clear();
        for(int i = 0; i < MAP_HEIGHT; i++)
        {
            for(int j = 0; j < MAP_WIDTH; j++)
            {
                auto color = COLOR_PAIR(COLORS[model->map[i][j]]);
                attron(color);
                printw("   ");
                attroff(color);
            }
            printw("\n");
        }
    }

    ~View()
    {
        endwin();
    }
};
