#include <iostream>
#include <vector>
#include <thread>

#include "Simulation.hpp"
#include "Position.hpp"

Simulation::Simulation()
{
    std::cout << "Start simulation\n";

    std::vector<Position> route;

    for (auto i = 7; i > -1; --i)
    {
        route.emplace_back(Position{4, i});
    }

    Map map;

    for (auto i = 0; i < 8; ++i)
    {
        map.fields[4][i].isAvailable = true;
    }

    auto t = std::thread(&Train::moveTrain, Train{0, 0, 0, route}, std::ref(map));
    t.join();
}

Simulation::~Simulation()
{
    std::cout << "\nEnd simulation\n";
}
