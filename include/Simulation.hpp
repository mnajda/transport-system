#pragma once

#include <thread>
#include <vector>
#include <array>
#include <mutex>

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
    void createTrains();
    void createTrainStations();
    void createThreads();

    Map map;
    std::vector<Train> trains;
    std::vector<TrainStation> trainStations;
    std::vector<std::thread> trainThreads;
    std::vector<std::thread> workerThreads;
    std::vector<std::thread> trainStationThreads;
    std::array<std::mutex, 4> trainLocks;
    std::array<std::mutex, 4> trainStationLocks;
};
