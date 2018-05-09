#pragma once

#include <string>
#include <string_view>

class TrainStation
{
public:
    TrainStation(int id) : stationId(id) {}
    void addCargo(std::string_view name, int amount);
    void takeCargo(std::string_view name, int amount);
private:
    int stationId, capacity;
    std::string cargoType;
};
