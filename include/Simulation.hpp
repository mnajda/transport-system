#pragma once

#include <thread>
#include <vector>

#include "Map.hpp"
#include "Train.hpp"
#include "TrainStation.hpp"

class Simulation
{
public:
    Simulation();
    ~Simulation();

    void start();

private:
    Map map;
    std::vector<Train> trains;
    std::vector<TrainStation> trainStations;
    std::vector<std::thread> trainThreads;
    std::vector<std::thread> workerThreads;
    std::vector<std::thread> trainStationThreads;
};
