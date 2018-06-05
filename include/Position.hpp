#pragma once

struct Position
{
    int x;
    int y;
    bool operator==(const Position& pos) { return x == pos.x && y == pos.y; }
};
