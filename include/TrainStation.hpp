#pragma once

#include <string>
#include <condition_variable>

#include "Position.hpp"

class TrainStation
{
public:
    TrainStation(int id, int posX, int posY);
    void trainEvent();
    void changeCargoAmount(const std::string& cargoName, int amount);
private:
    int stationId, capacity = 50;
    Position pos;
    std::string cargoType;
    std::condition_variable cv;
};
