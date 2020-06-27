#include "datamanager.h"

#include <QDebug>
#include <QDir>
#include "utils.h"


DataManager::DataManager()
{
    auto dirPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    if(!QDir().exists(dirPath)){
        QDir().mkpath(dirPath);
    }
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+ QDir::separator() + DB_PATH;
    qDebug() << path;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);

    if (!database.open())
    {
        qDebug() << database.lastError().text();
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS `Object` ("
                 "`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                 "`class`	INTEGER NOT NULL );");
    QSqlQuery query2;
    query2.exec("CREATE TABLE IF NOT EXISTS `Cells` ("
                                   "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                   "`x`	 INTEGER NOT NULL,"
                                   "`y`	 INTEGER NOT NULL,"
                                   "`object_id`	INTEGER NOT NULL,"
                                   "FOREIGN KEY(`object_id`) REFERENCES `Object`(`id`)"
                               ");");
}

void DataManager::save(const uint number, QList<Cell> cells)
{
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

QHash<uint, QList<Matrix>>* DataManager::read()
{
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
    QHash<uint, QList<Matrix>>* data = new QHash<uint, QList<uint**>>;
    QHash<uint, Object>::iterator it = objects.begin();
    while (it != objects.end()) {
        int className = it.value()[0].number;
        if(data->contains(className)){
            (*data)[className] << utils::collectMatrix(it.value());
        }else{
            QList<uint**> objectItems;
            (*data)[className] = objectItems;
            objectItems << utils::collectMatrix(it.value());
        }
        ++it;
    }

    return data;
}

