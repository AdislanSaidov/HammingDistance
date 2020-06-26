#pragma once

#include "dbhelper.h"

#include <QMainWindow>
#include "view.h"
#include "maincontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public View
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showPrediction(uint prediction);
    void showWeights(QStringList &);

private:
    Ui::MainWindow *ui;
    MainController* controller;

    void inject();
};
