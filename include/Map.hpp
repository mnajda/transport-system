#pragma once

#include <vector>

enum class FieldType
{
    Railway,
    SingleRailway,
    Station,
    Empty
};

struct Field
{
    FieldType type = Empty;
    bool isAvailable = false;
};

struct Map
{
    std::vector<std::vector<Field>> map;
};
