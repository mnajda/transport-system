#pragma once

#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "Map.hpp"
#include "Position.hpp"
#include "Train.hpp"

class TrainStation
{
public:
    TrainStation(int id, Position pos, Map& map, std::vector<Train>& trains, const std::string& unloaded,
                 const std::string& loaded);
    void trainEvent(std::array<std::mutex, 4>& trainLocks);
    void changeCargoAmount(std::array<std::mutex, 4>& trainStationLocks);

private:
    int stationId, capacity{10};
    Position pos;
    Map& map;
    std::vector<Train>& trains;
    std::string unloaded, loaded;
    std::map<std::string, int> cargo;
};
