#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Map.hpp"
#include "Position.hpp"

class Train
{
public:
    Train(int id, Position startPos, Map& map, const std::map<std::string, int>& cargo,
          std::vector<Position> trainRoute);
    void moveTrain();
    void changeCargoAmount(const std::string& name, int amount);
    Position getTrainPosition();
    std::map<std::string, int>& getTrainsCargo();

private:
    void freeRailway(const Position& pos) const;
    void singleRailway(const Position& pos) const;
    void arrivedToStation(const Position& pos) const;

    int trainId, capacity{10};
    Position position;
    Map& map;
    std::map<std::string, int> cargo;
    std::vector<Position> route;
};
