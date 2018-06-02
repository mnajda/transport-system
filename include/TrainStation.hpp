#pragma once

#include <map>
#include <string>
#include <vector>

#include "Map.hpp"
#include "Position.hpp"
#include "Train.hpp"

class TrainStation
{
public:
    TrainStation(int id, int posX, int posY, Map& map, std::vector<Train>& trains, const std::string& unloaded,
                 const std::string& loaded);
    void trainEvent();
    void changeCargoAmount();

private:
    int stationId, capacity{10};
    Position pos;
    Map& map;
    std::vector<Train>& trains;
    std::string unloaded, loaded;
    std::map<std::string, int> cargo;
};
