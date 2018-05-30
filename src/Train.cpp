#include <iostream>
#include <thread>
#include <chrono>

#include "Train.hpp"

Train::Train(int id, int startingX, int startingY, const std::vector<Position>& trainRoute)
    : trainId(id)
    , position({ startingX, startingY })
    , route(trainRoute)
{
    cargo.emplace_back(Cargo("Fruits", 0));
    cargo.emplace_back(Cargo("Vegetables", 0));
    cargo.emplace_back(Cargo("Beer", 0));
}

void Train::moveTrain(Map& map)
{
    for (const auto& pos : route)
    {
        std::unique_lock<std::mutex> lock(map.fields[pos.x][pos.y].mutex);
        map.fields[pos.x][pos.y].isAvailable = false;
        std::this_thread::sleep_for(std::chrono::milliseconds{500});
        std::cout <<  "#" << std::flush;
        map.fields[pos.x][pos.y].isAvailable = true;
    }
}

bool Train::changeCargoAmount(const std::string& name, int amount)
{

    return false;
}
