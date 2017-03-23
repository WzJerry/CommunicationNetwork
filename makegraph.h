#ifndef MAKEGRAPH_H
#define MAKEGRAPH_H
#include <QtGui>
#include <QPainter>
#include <QWidget>

class MakeGraph:public QWidget
{
    Q_OBJECT

public:
    MakeGraph(QWidget* parent =0);
    ~MakeGraph();
    int numOfCities;
    int numOfRoads;
    int ** randomRoads();
    //void judgeRedundancy();
    int findRoot(int x);
    int *pre;
    int *rank;

protected:
    void paintEvent(QPaintEvent * event);

};

#endif // MAKEGRAPH_H
