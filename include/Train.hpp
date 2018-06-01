#pragma once

#include <vector>
#include <utility>
#include <string>
#include <map>

#include "Position.hpp"
#include "Map.hpp"

class Train
{
public:
    Train(int id, int startingX, int startingY, const std::vector<Position>& trainRoute);
    void moveTrain(Map& map);
    bool changeCargoAmount(const std::string& name, int amount);
private:
    void freeRailway(Map& map, const Position& pos) const;
    void singleRailway(Map& map, const Position& pos) const;
    void arrivedToStation(Map& map, const Position& pos) const;

    int trainId, capacity;
    Position position;
    std::map<std::string, int> cargo;
    std::vector<Position> route;
};
