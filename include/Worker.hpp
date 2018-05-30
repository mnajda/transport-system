#pragma once

#include <string>

class Worker
{
public:
    Worker(int id) : workerId(id) {}
    void changeCargoAmount(const std::string& cargoName, int amount);
private:
    int workerId;
};
