#pragma once

#include <ncurses.h>
#include <vector>
#include <thread>

#include "Train.hpp"
#include "TrainStation.hpp"

class Visualization
{
public:
    Visualization(std::vector<Train>& trains, std::vector<TrainStation>& trainStations);
    ~Visualization();
    void start(bool& isRunning);

private:
    void startCurses();
    void createWindows();
    void displayTrains();
    void displayTrainStations();
    void displayTrainsCargo();
    void displayStationsCargo();

    int lines, columns;
    WINDOW* mapWindow;
    WINDOW* trainsWindow;
    WINDOW* stationsWindow;

    std::vector<Train>& trains;
    std::vector<TrainStation>& trainStations;
};
