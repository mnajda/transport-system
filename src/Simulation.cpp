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
        map[0][i].type = FieldType::Railway;
        map[4][i].type = FieldType::Railway;
        map[7][i].type = FieldType::Railway;

        map[0][i].isAvailable = true;
        map[4][i].isAvailable = true;
        map[7][i].isAvailable = true;
    }

    map[7][0].type = FieldType::Station;
    map[7][0].id = -2;
    map[7][7].type = FieldType::Station;
    map[7][7].id = -2;
    map[0][0].type = FieldType::Station;
    map[0][0].id = -2;
    map[0][7].type = FieldType::Station;
    map[0][7].id = -2;

    map[4][7].type = FieldType::SingleRailway;
    map[4][7].id = -3;
    map[4][0].type = FieldType::SingleRailway;
    map[4][0].id = -3;
}

Simulation::~Simulation()
{
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

    Visualization vis(trains, trainStations, map);
    vis.start(isRunning);
}

std::vector<Position> Simulation::makeRoute1()
{
    std::vector<Position> route1;

    for (auto i = 6; i > -1; --i)
    {
        route1.emplace_back(Position{4, i});
    }
    for (auto i = 5; i < 8; ++i)
    {
        route1.emplace_back(Position{i, 0});
    }
    for (auto i = 1; i < 8; ++i)
    {
        route1.emplace_back(Position{7, i});
    }
    for (auto i = 6; i > 3; --i)
    {
        route1.emplace_back(Position{i, 7});
    }

    return route1;
}

std::vector<Position> Simulation::makeRoute2()
{
    std::vector<Position> route2;

    for (auto i = 3; i > -1; --i)
    {
        route2.emplace_back(Position{i, 0});
    }
    for (auto i = 1; i < 8; ++i)
    {
        route2.emplace_back(Position{0, i});
    }
    for (auto i = 1; i < 5; ++i)
    {
        route2.emplace_back(Position{i, 7});
    }
    for (auto i = 6; i > -1; --i)
    {
        route2.emplace_back(Position{4, i});
    }

    return route2;
}

void Simulation::createTrains()
{
    std::array<unsigned char, 4> trainMarks = {'&', '^', '*', '%'};
    std::vector<Position> route1{makeRoute1()};
    std::vector<Position> route2{makeRoute2()};
    std::map<std::string, int> cargo;

    cargo.emplace(fruits, 2);
    cargo.emplace(vegetables, 2);
    cargo.emplace(beer, 2);

    trains.emplace_back(Train{0, trainMarks[0], {4, 1}, map, cargo, route1});
    trains.emplace_back(Train{1, trainMarks[1], {4, 6}, map, cargo, route1});
    trains.emplace_back(Train{2, trainMarks[2], {0, 1}, map, cargo, route2});
    trains.emplace_back(Train{3, trainMarks[3], {0, 6}, map, cargo, route2});
}

void Simulation::createTrainStations()
{
    trainStations.emplace_back(TrainStation{0, {7, 0}, map, trains, {vegetables, beer}});
    trainStations.emplace_back(TrainStation{1, {7, 7}, map, trains, {fruits, vegetables}});
    trainStations.emplace_back(TrainStation{2, {0, 0}, map, trains, {vegetables, fruits}});
    trainStations.emplace_back(TrainStation{3, {0, 7}, map, trains, {beer, vegetables}});
}

void Simulation::createThreads()
{
    for (auto i = 0; i < 4; ++i)
    {
        trainThreads.emplace_back(std::thread(&Train::moveTrain, &trains[i], std::ref(isRunning)));
    }
    for (auto i = 0; i < 4; ++i)
    {

        workerThreads.emplace_back(std::thread(&TrainStation::changeCargoAmount, &trainStations[i],
                                               std::ref(trainStationLocks), std::ref(isRunning)));
        trainStationThreads.emplace_back(
                std::thread(&TrainStation::trainEvent, &trainStations[i], std::ref(trainLocks), std::ref(isRunning)));
    }
}
