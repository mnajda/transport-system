#include "TrainStation.hpp"

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

TrainStation::TrainStation(int id, Position pos, Map& map, std::vector<Train>& trains, const std::string& loaded,
                           const std::string& unloaded)
    : stationId(id)
    , pos(pos)
    , map(map)
    , trains(trains)
    , unloaded(unloaded)
    , loaded(loaded)
{
    cargo.emplace(unloaded, 5);
    cargo.emplace(loaded, 5);
}

void TrainStation::trainEvent(std::array<std::mutex, 4>& trainLocks)
{
    auto& mapField = map[pos.x][pos.y];

    std::unique_lock<std::mutex> lock(mapField.mutex);
    mapField.cv.wait(lock, [&mapField] { return !mapField.isAvailable; });

    if (mapField.id != -1)
    {
        std::scoped_lock<std::mutex> trainLock(trainLocks[mapField.id]);
        trains[mapField.id].changeCargoAmount(loaded, 2);
        cargo[loaded] -= 2;
        trains[mapField.id].changeCargoAmount(unloaded, -2);
        cargo[unloaded] += 2;
    }

    mapField.isAvailable = true;
    mapField.cv.notify_one();
}

void TrainStation::changeCargoAmount(std::array<std::mutex, 4>& trainStationLocks)
{
    std::this_thread::sleep_for(std::chrono::seconds{3});
    std::scoped_lock<std::mutex> lock(trainStationLocks[stationId]);
    if (auto& product = cargo[loaded]; product < 7 && product + 2 <= capacity)
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
