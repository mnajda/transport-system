#pragma once

#include <vector>
#include <utility>
#include <string_view>
#include <map>

#include "Position.hpp"
#include "Map.hpp"

class Train
{
public:
    Train(int id, int startingX, int startingY, 
            std::map<std::string_view, int>& cargo, const std::vector<Position>& trainRoute);
    void moveTrain(Map& map);
    void changeCargoAmount(const std::string_view name, int amount);
private:
    void freeRailway(Map& map, const Position& pos) const;
    void singleRailway(Map& map, const Position& pos) const;
    void arrivedToStation(Map& map, const Position& pos) const;

    int trainId, capacity;
    Position position;
    std::map<std::string_view, int> cargo;
    std::vector<Position> route;
};
