#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

#include "Train.hpp"

Train::Train(int id, int startingX, int startingY, std::map<std::string_view, int>& cargo,
             const std::vector<Position>& trainRoute)
    : trainId(id)
    , position({startingX, startingY})
    , cargo(cargo)
    , route(trainRoute)
{
}

void Train::moveTrain(Map& map)
{
    for (const auto& pos : route)
    {
        auto& mapField = map[pos.x][pos.y];
        if (mapField.type == FieldType::Station)
        {
            arrivedToStation(map, pos);
            std::unique_lock<std::mutex> lock(mapField.mutex);
            mapField.cv.wait(lock, [&mapField] { return mapField.isAvailable; });
            mapField.id = -1;
        }
        else if (mapField.type == FieldType::SingleRailway)
        {
            singleRailway(map, pos);
        }
        else
        {
            freeRailway(map, pos);
        }
    }
}

void Train::changeCargoAmount(const std::string_view name, int amount)
{
    if (auto& product = cargo[name]; product + amount >= 0 && product + amount <= capacity)
    {
        product += amount;
        std::cout << name << " " + std::to_string(product) + "\n";
    }
}

void Train::freeRailway(Map& map, const Position& pos) const
{
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
    std::cout << "Passing through: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")\n";
}

void Train::singleRailway(Map& map, const Position& pos) const
{
    auto& mapField = map[pos.x][pos.y];

    std::lock_guard<std::mutex> lock(mapField.mutex);
    mapField.isAvailable = false;
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
    std::cout << "Passing through single railway: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")\n";
    mapField.isAvailable = true;
}

void Train::arrivedToStation(Map& map, const Position& pos) const
{
    auto& mapField = map[pos.x][pos.y];

    std::lock_guard<std::mutex> lock(mapField.mutex);
    mapField.id = trainId;
    std::cout << "Train " + std::to_string(trainId) + " arrived to station\n";
    mapField.isAvailable = false;

    std::this_thread::sleep_for(std::chrono::milliseconds{750});
    mapField.cv.notify_one();
}
