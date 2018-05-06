#pragma once

#include <string>

class TrainStation
{
public:
    TrainStation(int id) : stationId(id) {}
    void addCargo(const std::string& name, int amount);
    void takeCargo(const std::string& name, int amount);
private:
    int stationId, capacity;
    std::string cargoType;
};
