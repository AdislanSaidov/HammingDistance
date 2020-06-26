#pragma once
#include <QtCore>
#include <QHash>

struct Point
{
    Point(uint x, uint y): x(x), y(y){

    }

    uint x;
    uint y;
};

inline bool operator==(const Point &p1, const Point &p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}


inline uint qHash(const Point &key, uint seed)
{
    return qHash(key.x, seed) ^ key.x;
}

