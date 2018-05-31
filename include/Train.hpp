#pragma once

#include "Cargo.hpp"
#include "Position.hpp"
#include "Map.hpp"

#include <vector>
#include <utility>
#include <string>

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
    std::vector<Cargo> cargo;
    std::vector<Position> route;
};
