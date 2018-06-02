#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Map.hpp"
#include "Position.hpp"

class Train
{
public:
    Train(int id, int startingX, int startingY, Map& map, std::map<std::string, int>& cargo,
          const std::vector<Position>& trainRoute);
    void moveTrain();
    void changeCargoAmount(const std::string& name, int amount);

private:
    void freeRailway(const Position& pos) const;
    void singleRailway(const Position& pos) const;
    void arrivedToStation(const Position& pos) const;

    int trainId, capacity{10};
    Position position;
    Map& map;
    std::map<std::string, int> cargo;
    std::vector<Position> route;
};
