#pragma once

#include <QSqlError>
#include <QSqlQuery>

#include "models/point.h"
#include "models/cell.h"

typedef QList<Cell> Object;
typedef uint** Matrix;

class DataManager
{

public:
    DataManager();
    void save(const uint number, QList<Cell> cells);
    bool read(float* weights);
    QHash<uint, QList<Matrix>> *read();
private:
    QSqlDatabase database;

};
