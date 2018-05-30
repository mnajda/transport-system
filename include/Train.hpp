#pragma once

#include "Cargo.hpp"
#include "Position.hpp"
#include "Map.hpp"

#include <vector>
#include <utility>
#include <string>

class Train
{
public:
    Train(int id, int startingX, int startingY, Map& simMap, const std::vector<Position>& trainRoute);
    void moveTrain();
    bool changeCargoAmount(const std::string& name, int amount);
private:
    int trainId, capacity;
    Map& map;
    Position position;
    std::vector<Cargo> cargo;
    std::vector<Position> route;
};
