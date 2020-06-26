#pragma once

#include <QHash>
#include "models/cell.h"
#include "utils.h"

class Classifier
{
public:
    Classifier();
    ~Classifier();

    void init(QHash<uint, QList<uint **>>* objects);
    uint predict(uint **currentMatrix);
    void train(uint className, QList<Cell> cells);
    QStringList getWeightsPerClass();

private:
    int computeHammingDistance(uint **trainingMatrix, uint **currentMatrix);
    int computeMax(double *classes);
    QHash<uint, QList<uint **>> *objects;
    double classes[MAX_CLASSES_COUNT] = {};
};
