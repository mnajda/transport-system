#pragma once

#include <map>
#include <string_view>
#include <utility>
#include <vector>

#include "Map.hpp"
#include "Position.hpp"

class Train
{
public:
    Train(int id, int startingX, int startingY, std::map<std::string_view, int>& cargo,
          const std::vector<Position>& trainRoute);
    void moveTrain(Map& map);
    void changeCargoAmount(std::string_view name, int amount);

private:
    void freeRailway(Map& map, const Position& pos) const;
    void singleRailway(Map& map, const Position& pos) const;
    void arrivedToStation(Map& map, const Position& pos) const;

    int trainId, capacity{10};
    Position position;
    std::map<std::string_view, int> cargo;
    std::vector<Position> route;
};
