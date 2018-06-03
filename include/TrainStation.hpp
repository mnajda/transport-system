#pragma once

#include <map>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "Cargo.hpp"
#include "Map.hpp"
#include "Position.hpp"
#include "Train.hpp"

class TrainStation
{
public:
    TrainStation(int id, Position pos, Map& map, std::vector<Train>& trains, Cargo availableCargo);
    void trainEvent(std::array<std::mutex, 4>& trainLocks);
    void changeCargoAmount(std::array<std::mutex, 4>& trainStationLocks);
    Position getStationPosition();
    Cargo getAvailableCargo();
    std::map<std::string, int>& getCurrectCargo();

private:
    int stationId, capacity{10};
    Position pos;
    Map& map;
    std::vector<Train>& trains;
    Cargo availableCargo;
    std::map<std::string, int> cargo;
};
