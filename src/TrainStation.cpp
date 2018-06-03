#include "TrainStation.hpp"

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

TrainStation::TrainStation(int id, Position pos, Map& map, std::vector<Train>& trains, Cargo availableCargo)
    : stationId(id)
    , pos(pos)
    , map(map)
    , trains(trains)
    , availableCargo{std::move(availableCargo)}
{
    cargo.emplace(availableCargo.loaded, 5);
    cargo.emplace(availableCargo.unloaded, 5);
}

void TrainStation::trainEvent(std::array<std::mutex, 4>& trainLocks, bool& isRunning)
{
    while (isRunning)
    {
        auto& mapField = map[pos.x][pos.y];

        std::unique_lock<std::mutex> lock(mapField.mutex);
        mapField.cv.wait(lock, [&mapField] { return !mapField.isAvailable; });

        if (mapField.id != -1)
        {
            std::scoped_lock<std::mutex> trainLock(trainLocks[mapField.id]);
            trains[mapField.id].changeCargoAmount(availableCargo.loaded, 2);
            cargo[availableCargo.loaded] -= 2;
            trains[mapField.id].changeCargoAmount(availableCargo.unloaded, -2);
            cargo[availableCargo.unloaded] += 2;
        }

        mapField.isAvailable = true;
        mapField.cv.notify_one();
    }
}

void TrainStation::changeCargoAmount(std::array<std::mutex, 4>& trainStationLocks, bool& isRunning)
{
    while (isRunning)
    {
        std::this_thread::sleep_for(std::chrono::seconds{3});
        std::scoped_lock<std::mutex> lock(trainStationLocks[stationId]);
        if (auto& product = cargo[availableCargo.loaded]; product < 7 && product + 2 <= capacity)
        {
            product += 2;
        }
        if (auto& product = cargo[availableCargo.unloaded]; product > 5 && product - 2 >= 0)
        {
            product -= 2;
        }
    }
}
