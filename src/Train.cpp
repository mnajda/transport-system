#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

#include "Train.hpp"
#include "Map.hpp"

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
        if (map.fields[pos.x][pos.y].type == FieldType::Station)
        {
            arrivedToStation(map, pos);
            std::unique_lock<std::mutex> lock(map.fields[pos.x][pos.y].mutex);
            map.fields[pos.x][pos.y].cv.wait(lock, [&map, &pos] { return map.fields[pos.x][pos.y].isAvailable; });
        }
        else if (map.fields[pos.x][pos.y].type == FieldType::SingleRailway)
        {
            singleRailway(map, pos);
        }
        else
        {
            freeRailway(map, pos);
        }
    }
}

bool Train::changeCargoAmount(const std::string& name, int amount)
{

    return false;
}

void Train::freeRailway(Map& map, const Position& pos) const
{
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
    std::cout <<  "Passing through: (" + std::to_string(pos.x) 
                    + ", " + std::to_string(pos.y) + ")\n"  << std::flush;
}

void Train::singleRailway(Map& map, const Position& pos) const
{
    std::lock_guard<std::mutex> lock(map.fields[pos.x][pos.y].mutex);
    map.fields[pos.x][pos.y].isAvailable = false;
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
    std::cout <<  "Passing through single railway: (" + std::to_string(pos.x) 
                    + ", " + std::to_string(pos.y) + ")\n"  << std::flush;
    map.fields[pos.x][pos.y].isAvailable = true;
}

void Train::arrivedToStation(Map& map, const Position& pos) const
{
    std::lock_guard<std::mutex> lock(map.fields[pos.x][pos.y].mutex);
    std::cout << "Train " + std::to_string(trainId) + " arrived to station\n";
    map.fields[pos.x][pos.y].isAvailable = false;

    std::this_thread::sleep_for(std::chrono::milliseconds{750});
    map.fields[pos.x][pos.y].cv.notify_one();
}
