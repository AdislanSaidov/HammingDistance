#include "classifier.h"
#include <QDebug>

Classifier::Classifier()
{

}

void Classifier::init(QHash<uint, QList<uint **> > *objects)
{
    this->objects = objects;
}


int Classifier::computeHammingDistance(uint** trainingMatrix, uint** currentMatrix){
    uint distance = 0;
    for(int i = 0; i < COLUMN_COUNT; ++i){
        for(int j = 0; j < COLUMN_COUNT; ++j){
            qDebug() << trainingMatrix[i][j];
            if(trainingMatrix[i][j] != currentMatrix[i][j]){
                ++distance;
            }
        }
    }
    return distance;
}

int Classifier::computeMax(double* classes){
    double max = 0;
    uint index = 0;
    for(int i = 0; i < MAX_CLASSES_COUNT; ++i){
        if(max < classes[i]){
            max = classes[i];
            index = i;
        }
    }
    return index;
}

uint Classifier::predict(uint** currentMatrix){

    for(int i = 0; i < MAX_CLASSES_COUNT; ++i){
        qDebug() << i << " d "<<classes[i];
        classes[i] = 0;
    }
    double r = 0.0;

    QHash<uint, QList<uint**>>::iterator it = objects->begin();
    while(it != objects->end()){
        for(auto trainingMatrix: it.value()){
            r = computeHammingDistance(trainingMatrix, currentMatrix);
            classes[it.key()] = classes[it.key()] + 1000000/(1+r*r);
        }
        ++it;
    }

    uint max = computeMax(classes);
    qDebug() << "max: "<< max;
    return max;
}

QStringList Classifier::getWeightsPerClass(){
    QStringList stringList;
    for(int i = 0; i < MAX_CLASSES_COUNT; ++i){
        qDebug() << i << " debug "<<classes[i];
        stringList << QString::number(i) + " " + QString::number(classes[i]);
    }
    return stringList;
}

void Classifier::train(uint className, QList<Cell> cells)
{
    (*objects)[className] << collectMatrix(cells);
}
