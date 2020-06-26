#include "dbhelper.h"
#include "utils.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>



DbHelper::DbHelper()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(DB_PATH);

    if (!database.open())
    {
        qDebug() << database.lastError().text();
    }
}

void DbHelper::saveData(const uint number, const QSet<Point>* points)
{
    QList<Cell> cells = convertPointsToCells(points);

    QSqlQuery queryInsertObject;
    queryInsertObject.prepare("INSERT INTO Object (class) VALUES (:class)");
    queryInsertObject.bindValue(":class", number);
    queryInsertObject.exec();

    QSqlQuery querySelectObject;
    querySelectObject.exec("SELECT id FROM Object ORDER BY id DESC LIMIT 1");
    uint objectId;
    while (querySelectObject.next()) {
        objectId = querySelectObject.value(0).toInt();
    }

    QSqlQuery queryInsertCells;
    queryInsertCells.prepare("INSERT INTO Cells (object_id, x, y) VALUES (:object_id, :x, :y)");
    QSqlDatabase::database().transaction();
    for(auto c: cells){
        queryInsertCells.bindValue(":object_id", objectId);
        queryInsertCells.bindValue(":x", c.x);
        queryInsertCells.bindValue(":y", c.y);

        queryInsertCells.exec();
    }
    QSqlDatabase::database().commit();
}

QHash<uint, QList<uint**>> DbHelper::fetchData(){

    QSqlQuery query;
    QHash<uint, Object> objects;
    query.exec("SELECT class, x, y, object_id FROM Cells c INNER JOIN Object o ON c.object_id = o.id");
    while (query.next()) {
        Cell cell;
        cell.number = query.value(0).toInt();
        cell.x = query.value(1).toInt();
        cell.y = query.value(2).toInt();
        cell.objectId = query.value(3).toInt();
        if(objects.contains(cell.objectId)){
            objects[cell.objectId] << cell;
        }else{
            QList<Cell> cells;
            objects[cell.objectId] = cells;
            cells << cell;
        }

    }
    QHash<uint, QList<uint**>> data;
    QHash<uint, Object>::iterator it = objects.begin();
    while (it != objects.end()) {
        if(data.contains(it.value()[0].number)){
            data[it.value()[0].number] << collectMatrix(it.value());
        }else{
            QList<uint**> objectItems;
            data[it.value()[0].number] = objectItems;
            objectItems << collectMatrix(it.value());
        }
        ++it;
    }

    return data;
}
