#pragma once

#include <string_view>
#include <map>
#include <vector>

#include "Map.hpp"
#include "Position.hpp"
#include "Train.hpp"

class TrainStation
{
public:
    TrainStation(int id, int posX, int posY, Map& map, std::vector<Train>& trains, 
                                const std::string_view unloaded, const std::string_view loaded);
    void trainEvent();
    void changeCargoAmount();
private:
    int stationId, capacity = 50;
    Position pos;
    Map& map;
    std::vector<Train>& trains;
    std::string_view unloaded, loaded;
    std::map<std::string_view, int> cargo;
};
