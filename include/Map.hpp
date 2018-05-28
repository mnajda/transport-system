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
    FieldType type{FieldType::Empty};
    bool isAvailable{false};
};

struct Map
{
    Map() : map(8, std::vector<Field>(8)) {}
    std::vector<std::vector<Field>> map;
};
