#include "maincontroller.h"
#include "utils.h"

MainController::MainController(View *view, DataManager *dataManager, Classifier *classifier):
    view(view),
    dataManager(dataManager),
    classifier(classifier)
{
    auto objects = dataManager->read();
    classifier->init(objects);
}

void MainController::predict(QSet<Point>* points)
{
    if(points->size() == 0)
        return;
    auto cells = convertPointsToCells(points);
    auto currentMatrix = collectMatrix(cells);

    auto prediction = classifier->predict(currentMatrix);
    view->showPrediction(prediction);

    auto stringList = classifier->getWeightsPerClass();
    view->showWeights(stringList);
}


void MainController::train(uint className, QSet<Point>* points){
    if(points->size() == 0)
        return;
    QList<Cell> cells = convertPointsToCells(points);
    dataManager->save(className, cells);
    classifier->train(className, cells);
}

MainController::~MainController()
{
    delete dataManager;
//    delete view;
    delete classifier;
}
