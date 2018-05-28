#pragma once

#include <string>

class Worker
{
public:
    Worker(int id) : workerId(id) {}
    void loadStation(const std::string& cargoName, int amount);
    void unloadStation(const std::string& cargoName, int amount);
private:
    int workerId;
};
