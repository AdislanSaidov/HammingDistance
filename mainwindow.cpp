#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "utils.h"

typedef QList<Cell> Object;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumber->hide();
    ui->listWidget->hide();
    //clear
    connect(ui->btnClear, &QPushButton::clicked, this, [=]{
        ui->listWidget->clear();
        ui->openGLView->clear();
        ui->lcdNumber->hide();
        ui->listWidget->hide();
    });
    //train
    connect(ui->btnTrain, &QPushButton::clicked, this, [=]{
        controller->train(ui->spinBox->value(), ui->openGLView->collectPoints());
    });
    //predict
    connect(ui->btnDetect, &QPushButton::clicked, this, [=]{
        controller->predict(ui->openGLView->collectPoints());
    });
    inject();
}

void MainWindow::inject()
{
    auto dataManager = new DataManager();
    auto classifier = new Classifier();
    controller = new MainController(this, dataManager, classifier);
}

void MainWindow::showPrediction(uint prediction){
    ui->lcdNumber->show();
    ui->lcdNumber->display(QString::number(prediction));
}

void MainWindow::showWeights(QStringList& weights)
{
    ui->listWidget->show();
    ui->listWidget->clear();
    ui->listWidget->addItems(weights);
}


MainWindow::~MainWindow()
{
    delete ui;
}

