#pragma once

#include "models/point.h"
#include "models/cell.h"
#include <QSqlDatabase>

typedef QList<Cell> Object;

class DbHelper
{
public:
    DbHelper();

    void saveData(const uint number, const QSet<Point> *);
    QHash<uint, QList<uint **> > fetchData();
private:
    QSqlDatabase database;

};
