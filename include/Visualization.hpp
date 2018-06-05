#pragma once

#include <ncurses.h>
#include <vector>
#include <thread>

#include "Train.hpp"
#include "TrainStation.hpp"

class Visualization
{
public:
    Visualization(std::vector<Train>& trains, std::vector<TrainStation>& trainStations, Map& map);
    ~Visualization();
    void start(bool& isRunning);

private:
    void startCurses();
    void createWindows();
    void displayMap();
    void displayTrains();
    void displayTrainStations();
    void displaySingleRailway();
    void displayTrainsCargo();
    void displayStationsCargo();

    int lines, columns;
    WINDOW* mapWindow;
    WINDOW* trainsWindow;
    WINDOW* stationsWindow;

    Map& map;
    std::vector<Train>& trains;
    std::vector<TrainStation>& trainStations;
};
