#include "Train.hpp"

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <utility>

Train::Train(int id, Position startPos, Map& map, const std::map<std::string, int>& cargo,
             std::vector<Position> trainRoute)
    : trainId(id)
    , position(startPos)
    , map(map)
    , cargo(cargo)
    , route(std::move(trainRoute))
{
}

void Train::moveTrain(bool& isRunning)
{
    while (isRunning)
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
}

void Train::changeCargoAmount(const std::string& name, int amount)
{
    if (auto& product = cargo[name]; product + amount >= 0 && product + amount <= capacity)
    {
        product += amount;
    }
}

void Train::updatePosition(const Position& pos)
{
    position.x = pos.x;
    position.y = pos.y;
}

void Train::freeRailway(const Position& pos)
{
    updatePosition(pos);
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
}

void Train::singleRailway(const Position& pos)
{
    updatePosition(pos);
    auto& mapField = map[pos.x][pos.y];

    std::scoped_lock<std::mutex> lock(mapField.mutex);
    mapField.isAvailable = false;
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
    mapField.isAvailable = true;
}

void Train::arrivedToStation(const Position& pos)
{
    updatePosition(pos);
    auto& mapField = map[pos.x][pos.y];

    std::scoped_lock<std::mutex> lock(mapField.mutex);
    mapField.id = trainId;
    mapField.isAvailable = false;

    std::this_thread::sleep_for(std::chrono::milliseconds{750});
    mapField.cv.notify_one();
}

Position Train::getTrainPosition() const
{
    return position;
}

std::map<std::string, int>& Train::getTrainsCargo()
{
    return cargo;
}
