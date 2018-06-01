#include "TrainStation.hpp"

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

TrainStation::TrainStation(int id, int posX, int posY, Map& map, std::vector<Train>& trains, 
                                    const std::string_view loaded, const std::string_view unloaded)
    : stationId(id)
    , pos(Position{ posX, posY })
    , map(map)
    , trains(trains)
    , unloaded(unloaded)
    , loaded(loaded)
{
    cargo.emplace(loaded, 5);
    cargo.emplace(unloaded, 5);
}

void TrainStation::trainEvent()
{
    std::unique_lock<std::mutex> lock(map.fields[pos.x][pos.y].mutex);
    map.fields[pos.x][pos.y].cv.wait(lock, [this] { return !map.fields[pos.x][pos.y].isAvailable; });

    if (map.fields[pos.x][pos.y].id == -1)
    {
        map.fields[pos.x][pos.y].isAvailable = true;
        map.fields[pos.x][pos.y].cv.notify_one();    
    }
    else
    {
        trains[map.fields[pos.x][pos.y].id].changeCargoAmount(loaded, 2);
        cargo[loaded] -= 2;
        trains[map.fields[pos.x][pos.y].id].changeCargoAmount(unloaded, -2);
        cargo[unloaded] += 2;

        map.fields[pos.x][pos.y].isAvailable = true;
        map.fields[pos.x][pos.y].cv.notify_one();
    }
}

void TrainStation::changeCargoAmount()
{
    std::this_thread::sleep_for(std::chrono::seconds{3});
    if (auto& product = cargo[loaded]; product < 7 &&  product + 2 <= 10)
    {
        product += 2;
        std::cout << "New value: " + std::to_string(product) + "\n";
    }
    if (auto& product = cargo[unloaded]; product > 5 && product - 2 >= 0)
    {
        product -= 2;
        std::cout << "New value: " + std::to_string(product) + "\n";
    }
}
