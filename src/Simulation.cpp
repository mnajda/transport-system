#include <iostream>
#include <vector>

#include "Simulation.hpp"
#include "Position.hpp"

Simulation::Simulation()
{
    std::vector<Position> route;

    for (auto i = 0; i < 8; ++i)
    {
        route.emplace_back(Position{i, 4});
    }

    Map map;

    Train train{0, 0, 0, map, route};

    for (const auto& row : map.map)
    {
        for (const auto& field : row)
        {
            std::cout << field.isAvailable << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Simulation::~Simulation()
{
    std::cout << "dtor\n";
}
