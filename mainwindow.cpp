#include "mainwindow.h"
#include "input.h"
#include "time.h"
#include <iostream>
#include <QTime>
//#include <QtTest/QTest>
using namespace std;
#include <QtGui>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("CommunicationNetwork"));
    makeGraph1.numOfCities=numOfCities;
    makeGraph1.numOfRoads=numOfRoads;
    makeGraph2.numOfCities=numOfCities;
    makeGraph2.numOfRoads=numOfRoads;
    makeGraph3.numOfCities=numOfCities;
    makeGraph3.numOfRoads=numOfRoads;
    //Button of question1
    inputAction=new QAction(tr("输入"),this);
    connect(inputAction,&QAction::triggered,this,&MainWindow::inputDialog);
    judgeRedundancyAction=new QAction(tr("判断冗余边"));
    connect(judgeRedundancyAction,&QAction::triggered,this,&MainWindow::makeGraph);
    //Button of question2
    judgeReliabilityAction=new QAction(tr("判断网络是否可靠"),this);
    connect(judgeReliabilityAction,&QAction::triggered,this,&MainWindow::judgeReliability);
    //Button of question3
    markCityAction=new QAction(tr("标记重要城市"),this);
    connect(markCityAction,&QAction::triggered,this,&MainWindow::markCity);

    //Menu
    QMenu *menu1=menuBar()->addMenu(tr("问题1"));
    menu1->addAction(inputAction);
    menu1->addAction(judgeRedundancyAction);
    QMenu *menu2=menuBar()->addMenu(tr("问题2"));
    menu2->addAction(judgeReliabilityAction);
    QMenu *menu3=menuBar()->addMenu(tr("问题3"));
    menu3->addAction(markCityAction);

    //Initialize
    resize(600, 500);               //窗口大小
    //memset(a, 0, 19 * 19 * sizeof(int));
}

MainWindow::~MainWindow()
{

}

void MainWindow::inputDialog()
{
    inputDialog1.show();
}

void MainWindow::makeGraph()
{
    makeGraph1.show();

}


void MainWindow::judgeReliability()
{
    makeGraph2.show();
}

void MainWindow::markCity()
{
    makeGraph3.show();
}
