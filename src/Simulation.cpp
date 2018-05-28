#include <iostream>

#include "Simulation.hpp"

Simulation::Simulation()
{
    Map map;
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
