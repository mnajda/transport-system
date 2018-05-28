#include "Train.hpp"

Train::Train() : trainId(id)
{
    cargo.emplace_back(Cargo("Fruits", 0))
}

void Train::move()
{

}

bool Train::loadCargo(const std::string& name, int amount)
{

}

bool Train::unloadCargo(const std::string& name, int amount)
{

}
