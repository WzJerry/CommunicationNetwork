#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <input.h>
#include "makegraph.h"
#include "makegraph2.h"
#include "makegraph3.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    InputDialog inputDialog1;
    int numOfCities=inputDialog1.getNumOfCities();
    int numOfRoads=inputDialog1.getNumOfRoads();
    MakeGraph makeGraph1;
    //int **randomRoads();
    void makeGraph();
    void judgeReliability();
    MakeGraph2 makeGraph2;
    MakeGraph3 makeGraph3;
    void markCity();
private:
    QAction *inputAction;
    QAction *judgeRedundancyAction;
    QAction *judgeReliabilityAction;
    QAction *markCityAction;

private slots:
    void inputDialog();
};

#endif // MAINWINDOW_H
