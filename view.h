#pragma once
#include <QString>

class View
{
public:
    virtual void showPrediction(uint prediction) = 0;
    virtual void showWeights(QStringList&) = 0;
};
