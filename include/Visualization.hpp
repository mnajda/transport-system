#pragma once

#include <ncurses.h>

class Visualization
{
public:
    Visualization();
    ~Visualization();
private:
    int lines, columns;
    WINDOW* mapWindow;
    WINDOW* trainsWindow;
    WINDOW* stationsWindow;
};
