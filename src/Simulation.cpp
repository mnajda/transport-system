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
    std::cout << "Start simulation\n\n";

    for (auto i = 0; i < 8; ++i)
    {
        map[4][i].type = FieldType::Railway;
        map[4][i].isAvailable = true;
    }

    map[4][4].type = FieldType::Station;
    map[4][6].type = FieldType::SingleRailway;
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
    std::cout << "\nEnd simulation\n";
}

void Simulation::start()
{
    std::vector<Position> route;
    std::map<std::string, int> cargo;

    for (auto i = 7; i > -1; --i)
    {
        route.emplace_back(Position{4, i});
    }

    cargo.emplace(fruits, 0);
    cargo.emplace(vegetables, 0);
    cargo.emplace(beer, 2);

    trains.emplace_back(Train{0, 0, 0, map, cargo, route});
    trainStations.emplace_back(TrainStation{0, 4, 4, map, trains, vegetables, beer});

    trainThreads.emplace_back(std::thread(&Train::moveTrain, trains[0]));
    workerThreads.emplace_back(std::thread(&TrainStation::changeCargoAmount, trainStations[0]));
    trainStationThreads.emplace_back(std::thread(&TrainStation::trainEvent, trainStations[0]));
}
