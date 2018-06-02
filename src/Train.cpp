#include "Train.hpp"

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

Train::Train(int id, int startingX, int startingY, Map& map, std::map<std::string, int>& cargo,
             const std::vector<Position>& trainRoute)
    : trainId(id)
    , position({startingX, startingY})
    , map(map)
    , cargo(cargo)
    , route(trainRoute)
{
}

void Train::moveTrain()
{
    for (const auto& pos : route)
    {
        auto& mapField = map[pos.x][pos.y];
        if (mapField.type == FieldType::Station)
        {
            arrivedToStation(pos);
            std::unique_lock<std::mutex> lock(mapField.mutex);
            mapField.cv.wait(lock, [&mapField] { return mapField.isAvailable; });
            mapField.id = -1;
        }
        else if (mapField.type == FieldType::SingleRailway)
        {
            singleRailway(pos);
        }
        else
        {
            freeRailway(pos);
        }
    }
}

void Train::changeCargoAmount(const std::string& name, int amount)
{
    if (auto& product = cargo[name]; product + amount >= 0 && product + amount <= capacity)
    {
        product += amount;
        std::cout << name << " " + std::to_string(product) + "\n";
    }
}

void Train::freeRailway(const Position& pos) const
{
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
    std::cout << "Passing through: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")\n";
}

void Train::singleRailway(const Position& pos) const
{
    auto& mapField = map[pos.x][pos.y];

    std::lock_guard<std::mutex> lock(mapField.mutex);
    mapField.isAvailable = false;
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
    std::cout << "Passing through single railway: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")\n";
    mapField.isAvailable = true;
}

void Train::arrivedToStation(const Position& pos) const
{
    auto& mapField = map[pos.x][pos.y];

    std::lock_guard<std::mutex> lock(mapField.mutex);
    mapField.id = trainId;
    std::cout << "Train " + std::to_string(trainId) + " arrived to station\n";
    mapField.isAvailable = false;

    std::this_thread::sleep_for(std::chrono::milliseconds{750});
    mapField.cv.notify_one();
}
