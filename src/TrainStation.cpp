#include "TrainStation.hpp"

#include <iostream>
#include <mutex>
#include <condition_variable>

TrainStation::TrainStation(int id, int posX, int posY, Map& map)
    : stationId(id)
    , pos(Position{ posX, posY })
    , map(map)
{
}

void TrainStation::trainEvent()
{
    std::unique_lock<std::mutex> lock(map.fields[pos.x][pos.y].mutex);
    map.fields[pos.x][pos.y].cv.wait(lock, [this] { return !map.fields[pos.x][pos.y].isAvailable; });
    std::cout << "trainEvent()\n";
    map.fields[pos.x][pos.y].isAvailable = true;
    map.fields[pos.x][pos.y].cv.notify_one();
}

void TrainStation::changeCargoAmount(const std::string& cargoName, int amount)
{
    
}
