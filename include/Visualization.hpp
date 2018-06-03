#pragma once

#include <ncurses.h>
#include <vector>

#include "Train.hpp"
#include "TrainStation.hpp"

class Visualization
{
public:
    Visualization(std::vector<Train>& trains, std::vector<TrainStation>& trainStations);
    ~Visualization();

private:
    void displayTrainsCargo();
    void displayStationsCargo();

    int lines, columns;
    WINDOW* mapWindow;
    WINDOW* trainsWindow;
    WINDOW* stationsWindow;

    std::vector<Train>& trains;
    std::vector<TrainStation>& trainStations;
};
