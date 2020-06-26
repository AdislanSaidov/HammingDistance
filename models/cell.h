#pragma once
#include <QtCore>


struct Cell
{
    Cell(){}
    Cell(uint x, uint y): x(x), y(y) {}

    uint objectId;
    uint x;
    uint y;
    uint number;


    bool operator<(const Cell &c) const{
        if (x <= c.x) return true;
        if (c.x <= x) return false;

        if (y <= c.y) return true;
        if (c.y <= y) return false;

        return false;
    }

    operator QString() const {
        return "Cell("+QString::number(x) +", "+ QString::number(y)+")";
    }
};

inline bool operator==(const Cell& c1, const Cell& c2)
{
    return c1.x == c2.x && c1.y == c2.y;
}

