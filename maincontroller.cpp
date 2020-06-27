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
    auto cells = utils::convertPointsToCells(points);
    auto currentMatrix = utils::collectMatrix(cells);

    auto prediction = classifier->predict(currentMatrix);
    view->showPrediction(prediction);

    auto stringList = classifier->getWeightsPerClass();
    view->showWeights(stringList);
}


void MainController::train(uint className, QSet<Point>* points){
    if(points->size() == 0)
        return;
    QList<Cell> cells = utils::convertPointsToCells(points);
    dataManager->save(className, cells);
    classifier->train(className, cells);
}

MainController::~MainController()
{
    delete dataManager;
    delete classifier;
}
