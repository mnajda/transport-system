#pragma once

#include <thread>
#include <vector>
#include <array>
#include <mutex>

#include "Map.hpp"
#include "Train.hpp"
#include "Position.hpp"
#include "TrainStation.hpp"
#include "Visualization.hpp"

class Simulation
{
public:
    Simulation();
    ~Simulation();

    void start();

private:
    std::vector<Position> makeRoute1();
    std::vector<Position> makeRoute2();
    void createTrains();
    void createTrainStations();
    void createThreads();

    bool isRunning{true};
    Map map;
    std::vector<Train> trains;
    std::vector<TrainStation> trainStations;
    std::vector<std::thread> trainThreads;
    std::vector<std::thread> workerThreads;
    std::vector<std::thread> trainStationThreads;
    std::array<std::mutex, 4> trainLocks;
    std::array<std::mutex, 4> trainStationLocks;
};
