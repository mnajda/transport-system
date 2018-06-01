#include "TrainStation.hpp"

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

TrainStation::TrainStation(int id, int posX, int posY, Map& map)
    : stationId(id)
    , pos(Position{ posX, posY })
    , map(map)
{
    cargo.emplace("Vegetables", 8);
}

void TrainStation::trainEvent()
{
    std::unique_lock<std::mutex> lock(map.fields[pos.x][pos.y].mutex);
    map.fields[pos.x][pos.y].cv.wait(lock, [this] { return !map.fields[pos.x][pos.y].isAvailable; });
    std::cout << "trainEvent()\n";
    map.fields[pos.x][pos.y].isAvailable = true;
    map.fields[pos.x][pos.y].cv.notify_one();
}

void TrainStation::changeCargoAmount()
{
    std::this_thread::sleep_for(std::chrono::seconds{3});
    for (auto& product : cargo)
    {
        if (product.second > 7)
        {
            std::cout << "Remove " + product.first + " ";
            product.second -= 3;
            std::cout << "New value: " + std::to_string(product.second) + "\n";
        }
        else if (product.second < 3)
        {
            std::cout << "Add " + product.first + " ";
            product.second += 3;
            std::cout << "New value: " + std::to_string(product.second) + "\n";
        }
    }
}
