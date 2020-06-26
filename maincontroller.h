#pragma once

#include "datamanager.h"
#include "view.h"
#include "classifier.h"
typedef QList<Cell> Object;

class MainController
{
public:
    MainController(View* view, DataManager* dataManager, Classifier* classifier);
    ~MainController();

    void predict(QSet<Point> *points);

    void train(uint className, QSet<Point> *points);


private:
    DataManager* dataManager;
    View* view;
    Classifier* classifier;

};
