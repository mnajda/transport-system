#include <iostream>
#include <vector>
#include <thread>

#include "Simulation.hpp"
#include "Position.hpp"
#include "Map.hpp"

Simulation::Simulation()
{
    std::cout << "Start simulation\n\n";

    trainStations.emplace_back(TrainStation{0, 4, 4, map});

    for (auto i = 0; i < 8; ++i)
    {
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
    for (auto i = 7; i > -1; --i)
    {
        route.emplace_back(Position{4, i});
    }

    trainThreads.emplace_back(std::thread(&Train::moveTrain, Train{0, 0, 0, route}, std::ref(map)));
    workerThreads.emplace_back(std::thread(&TrainStation::changeCargoAmount, trainStations[0]));
    trainStationThreads.emplace_back(std::thread(&TrainStation::trainEvent, trainStations[0]));
}
