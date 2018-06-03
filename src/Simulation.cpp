#include "Simulation.hpp"

#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "Map.hpp"
#include "Position.hpp"

namespace
{
constexpr auto fruits = "Fruits";
constexpr auto vegetables = "Vegetables";
constexpr auto beer = "Beer";
} // namespace

Simulation::Simulation()
{
    for (auto i = 0; i < 8; ++i)
    {
        map[4][i].type = FieldType::Railway;
        map[4][i].isAvailable = true;
    }

    map[4][4].type = FieldType::Station;
    map[4][6].type = FieldType::SingleRailway;

    createTrains();
    createTrainStations();
}

Simulation::~Simulation()
{
    visualization.join();
    for (auto& train : trainThreads)
    {
        train.join();
    }
    for (auto& worker : workerThreads)
    {
        worker.join();
    }
    for (auto& station : trainStationThreads)
    {
        station.join();
    }
}

void Simulation::start()
{
    createTrains();
    createTrainStations();
    createThreads();

    Visualization vis(trains, trainStations);
    vis.start(isRunning);
}

void Simulation::createTrains()
{
    std::vector<Position> route;
    std::map<std::string, int> cargo;

    for (auto i = 7; i > -1; --i)
    {
        route.emplace_back(Position{4, i});
    }
    for (auto i = 5; i < 8; ++i)
    {
        route.emplace_back(Position{i, 0});
    }
    for (auto i = 1; i < 8; ++i)
    {
        route.emplace_back(Position{7, i});
    }
    for (auto i = 6; i > 3; --i)
    {
        route.emplace_back(Position{i, 7});
    }

    cargo.emplace(fruits, 2);
    cargo.emplace(vegetables, 2);
    cargo.emplace(beer, 2);

    trains.emplace_back(Train{0, {4, 7}, map, cargo, route});
    //trains.emplace_back(Train{1, {2, 2}, map, cargo, route});
}

void Simulation::createTrainStations()
{
    trainStations.emplace_back(TrainStation{0, {4, 4}, map, trains, {vegetables, beer}});
    //trainStations.emplace_back(TrainStation{1, {7, 3}, map, trains, {fruits, vegetables}});
}

void Simulation::createThreads()
{
    trainThreads.emplace_back(std::thread(&Train::moveTrain, &trains[0], std::ref(isRunning)));
    workerThreads.emplace_back(std::thread(&TrainStation::changeCargoAmount, &trainStations[0],
                                           std::ref(trainStationLocks), std::ref(isRunning)));
    trainStationThreads.emplace_back(
        std::thread(&TrainStation::trainEvent, &trainStations[0], std::ref(trainLocks), std::ref(isRunning)));
}
