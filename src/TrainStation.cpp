#include "TrainStation.hpp"

TrainStation::TrainStation(int id, int posX, int posY)
    : stationId(id)
    , pos(Position{ posX, posY })
{
}

void TrainStation::trainEvent()
{

}

void TrainStation::changeCargoAmount(const std::string& cargoName, int amount)
{
    
}
