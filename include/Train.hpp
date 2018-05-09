#pragma once

#include "Cargo.hpp"

#include <vector>
#include <string>
#include <string_view>

class Train
{
public:
    Train(int id) : trainId(id) {}
    bool loadCargo(std::string_view name, int amount);
    bool unloadCargo(std::string_view name, int amount);
private:
    int trainId, capacity;
    std::vector<Cargo> cargo;
};
