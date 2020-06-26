#pragma once

#include <QtCore>
#include "models/cell.h"
#include "models/point.h"
#include "constants.h"


static QList<Cell> reduce(QList<Cell> &cells){
    QHash<Cell, uint> map;
    for(auto cell: cells) {
        if(map.contains(cell)){
            map[cell] = map[cell]+1;
        }else{
            map[cell] = 1;
        }
    }
    QList<Cell> resultCells;
    QHash<Cell, uint>::iterator it = map.begin();
    while (it != map.end()) {
        if(it.value() >= POINTS_PER_CELL){
            resultCells << it.key();
        }
        ++it;
    }

    return resultCells;
}

static QList<Cell> convertPointsToCells(const QSet<Point>* points){
    QList<Cell> cells;
    for(auto p: *points){
        //        qDebug() << "current: x = "<<p.x <<" y = "<< p.y;
        uint xp = -1;
        uint yp = -1;
        for(uint i = 0; i < COLUMN_COUNT; ++i){
            uint start = i * COLUMN_WIDTH;
            uint end = start + COLUMN_WIDTH;
            bool isXinRange = start <= p.x && p.x < end;

            if(isXinRange){
                xp = i;
            }
            bool isYinRange = start <= p.y && p.y < end;
            if(isYinRange){
                yp = i;
            }
        }
        cells << Cell(xp, yp);
    }

    return reduce(cells);
}


static uint** collectMatrix(QList<Cell> &cells){
    uint** matrix = new uint*[COLUMN_COUNT];
    for(uint i = 0; i < COLUMN_COUNT; ++i){
        matrix[i] = new uint[COLUMN_COUNT]();
    }

    for(auto c: cells){
        matrix[c.x][c.y] = 1;
    }
    return matrix;
}


