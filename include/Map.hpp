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
    int id{-1};
    std::mutex mutex;
    std::condition_variable cv;
};

struct Map
{
    std::array<std::array<Field, 8>, 8> fields;
    std::array<Field, 8>& operator[](int row) { return fields[row]; }
};
