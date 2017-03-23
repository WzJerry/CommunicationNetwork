#ifndef ALGORITHMFORQ1_H
#define ALGORITHMFORQ1_H
#include "input.h"
#include "mainwindow.h"

class AlgorithmForQ1
{
public :
    AlgorithmForQ1();
    ~AlgorithmForQ1();
    int** randomRoads();
private:
    MainWindow mainWindow1;
    int numOfCities=mainWindow1.inputDialog1.getNumOfCities();
    int numOfRoads=mainWindow1.inputDialog1.getNumOfRoads();
    int **roadGraphMatrix={0};


};

#endif // ALGORITHMFORQ1_H
