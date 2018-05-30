#include <iostream>

#include "Train.hpp"

Train::Train(int id, int startingX, int startingY, Map& simMap, const std::vector<Position>& trainRoute)
    : trainId(id)
    , map(simMap)
    , position({ startingX, startingY })
    , route(trainRoute)
{
    cargo.emplace_back(Cargo("Fruits", 0));
    cargo.emplace_back(Cargo("Vegetables", 0));
    cargo.emplace_back(Cargo("Meat", 0));

    for (const auto& pos :route)
    {
        std::cout << pos.x << " " << pos.y << "\n";
    }
}

void Train::moveTrain()
{

}

bool Train::changeCargoAmount(const std::string& name, int amount)
{

    return false;
}
