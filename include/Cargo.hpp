#pragma once

#include <string>

struct Cargo
{
    Cargo(const std::string& cargoName, int cargoAmount) 
        : name(cargoName)
        , amount(cargoAmount)
    {
    }
    
    std::string name;
    int amount;
};
