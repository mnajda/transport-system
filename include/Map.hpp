#pragma once

#include <array>
#include <condition_variable>
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
    std::condition_variable cv;
};

struct Map
{
    std::array<std::array<Field, 8>, 8> fields;
};
