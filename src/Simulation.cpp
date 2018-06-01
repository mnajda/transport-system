#include <iostream>
#include <vector>
#include <string_view>
#include <map>
#include <thread>

#include "Simulation.hpp"
#include "Position.hpp"
#include "Map.hpp"

namespace
{
    constexpr std::string_view fruits = "Fruits";
    constexpr std::string_view vegetables = "Vegetables";
    constexpr std::string_view beer = "Beer";
} // namespace

Simulation::Simulation()
{
    std::cout << "Start simulation\n\n";

    for (auto i = 0; i < 8; ++i)
    {
        map.fields[4][i].type = FieldType::Railway;
        map.fields[4][i].isAvailable = true;
    }

    map.fields[4][4].type = FieldType::Station;
    map.fields[4][6].type = FieldType::SingleRailway;
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
    std::map<std::string_view, int> cargo;

    for (auto i = 7; i > -1; --i)
    {
        route.emplace_back(Position{4, i});
    }

    cargo.emplace(fruits, 0);
    cargo.emplace(vegetables, 0);
    cargo.emplace(beer, 2);

    trains.emplace_back(Train{0, 0, 0, cargo, route});
    trainStations.emplace_back(TrainStation{0, 4, 4, map, trains, vegetables, beer});

    trainThreads.emplace_back(std::thread(&Train::moveTrain, trains[0], std::ref(map)));
    workerThreads.emplace_back(std::thread(&TrainStation::changeCargoAmount, trainStations[0]));
    trainStationThreads.emplace_back(std::thread(&TrainStation::trainEvent, trainStations[0]));
}
