#pragma once

#include <string>
#include <map>

#include "Map.hpp"
#include "Position.hpp"

class TrainStation
{
public:
    TrainStation(int id, int posX, int posY, Map& map);
    void trainEvent();
    void changeCargoAmount();
private:
    int stationId, capacity = 50;
    Position pos;
    Map& map;
    std::map<std::string, int> cargo;
};
