#pragma once

#include "Cargo.hpp"

#include <vector>
#include <string>

class Train
{
public:
    Train(int id) : trainId(id) {}
    bool loadCargo(const std::string& name, int amount);
    bool unloadCargo(const std::string& name, int amount);
private:
    int trainId, capacity;
    std::vector<Cargo> cargo;
};
