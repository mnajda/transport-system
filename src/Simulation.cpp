#include <iostream>
#include <vector>
#include <thread>

#include "Simulation.hpp"
#include "Position.hpp"
#include "Map.hpp"

Simulation::Simulation()
{
    std::cout << "Start simulation\n";

    std::vector<Position> route;
    trainStations.emplace_back(TrainStation{0, 4, 4});

    for (auto i = 7; i > -1; --i)
    {
        route.emplace_back(Position{4, i});
    }

    for (auto i = 0; i < 8; ++i)
    {
        map.fields[4][i].isAvailable = true;
    }

    map.fields[4][4].type = FieldType::Station;

    trainThreads.emplace_back(std::thread(&Train::moveTrain, Train{0, 0, 0, route}, std::ref(map)));
    trainStationThreads.emplace_back(std::thread(&TrainStation::trainEvent, trainStations[0]));
}

Simulation::~Simulation()
{
    for (auto& train : trainThreads)
    {
        train.join();
    }
    for (auto& station : trainStationThreads)
    {
        station.join();
    }
    std::cout << "\nEnd simulation\n";
}
