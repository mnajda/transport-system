#pragma once

#include <string>

#include "Map.hpp"
#include "Position.hpp"

class TrainStation
{
public:
    TrainStation(int id, int posX, int posY, Map& map);
    void trainEvent();
    void changeCargoAmount(const std::string& cargoName, int amount);
private:
    int stationId, capacity = 50;
    Position pos;
    Map& map;
    std::string cargoType;
};
