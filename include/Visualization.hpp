#pragma once

#include <ncurses.h>
#include <thread>
#include <vector>

#include "Train.hpp"
#include "TrainStation.hpp"

class Visualization
{
public:
    Visualization(std::vector<Train>& trains, std::vector<TrainStation>& trainStations, Map& map);
    ~Visualization();
    void start(bool& isRunning);
    void stopOnButtonPress(bool& isRunning);

private:
    void startCurses();
    void createWindows();
    void displayMap();
    void displayTrains();
    void displayTrainStations();
    void displaySingleRailway();
    void displayTrainsCargo();
    void displayStationsCargo();
    void notifyStation(Position pos);

    int lines, columns;
    WINDOW* mapWindow;
    WINDOW* trainsWindow;
    WINDOW* stationsWindow;

    Map& map;
    std::vector<Train>& trains;
    std::vector<TrainStation>& trainStations;
};
