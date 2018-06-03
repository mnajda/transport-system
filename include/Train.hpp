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
    void moveTrain(bool& isRunning);
    void changeCargoAmount(const std::string& name, int amount);
    Position getTrainPosition() const { return position; }
    std::map<std::string, int>& getTrainsCargo() { return cargo; }

private:
    void updatePosition(const Position& pos);
    void freeRailway(const Position& pos);
    void singleRailway(const Position& pos);
    void arrivedToStation(const Position& pos);

    int trainId, capacity{10};
    Position position;
    Map& map;
    std::map<std::string, int> cargo;
    std::vector<Position> route;
};
