#pragma once

#include <array>
#include <mutex>

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
    std::mutex mutex;
};

struct Map
{
    std::array<std::array<Field, 8>, 8> map;
};
