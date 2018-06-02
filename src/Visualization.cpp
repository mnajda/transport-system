#include "Visualization.hpp"

#include <iostream>

Visualization::Visualization()
{
    initscr();
    start_color();
    curs_set(0);
    refresh();

    init_pair(1, COLOR_BLUE, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_WHITE);

    getmaxyx(stdscr, columns, lines);
    mapWindow = newwin(columns, lines / 2, 0, 50);
    trainsWindow = newwin(columns, (lines / 4) + 3, 0, 0);
    stationsWindow = newwin(columns, lines / 4, 0, lines - 46);

    wbkgd(mapWindow, COLOR_PAIR(1));
    wbkgd(trainsWindow, COLOR_PAIR(2));
    wbkgd(stationsWindow, COLOR_PAIR(2));

    box(mapWindow, 0, 0);
    box(trainsWindow, 0, 0);
    box(stationsWindow, 0, 0);

    wrefresh(mapWindow);
    wrefresh(trainsWindow);
    wrefresh(stationsWindow);
}

Visualization::~Visualization()
{
    delwin(mapWindow);
    delwin(trainsWindow);
    delwin(stationsWindow);

    endwin();
}
