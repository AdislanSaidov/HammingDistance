#pragma once

#include <QDebug>
#include "models/cell.h"
#include "models/point.h"
#include "constants.h"

namespace utils {
    //removing redundant cells
    QList<Cell> reduce(QList<Cell> &cells);

    // relating to cells
    QList<Cell> convertPointsToCells(const QSet<Point>* points);

    // create matrix from cells
    uint** collectMatrix(QList<Cell> &cells);

}



