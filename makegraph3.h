#ifndef MAKEGRAPH3_H
#define MAKEGRAPH3_H
#include <QtGui>
#include <QPainter>
#include <QWidget>
#define MAX_VERTEX_NUM 20

class MakeGraph3:public QWidget
{
    Q_OBJECT

public:
    MakeGraph3(QWidget* parent =0);
    ~MakeGraph3();
    int numOfCities;
    int numOfRoads;

    typedef struct
    {
        int weight;
    }Adj,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    typedef struct
    {
        AdjMatrix arc;
        int vexnum;
    }MGraph ;
    void CreateMGraph(MGraph &M);
    void print(MGraph m);
    bool Connectivity_BFS(MGraph m);
    void deletePoint(MGraph m);
    int *recordKeyCity;

protected:
    void paintEvent(QPaintEvent * event);

};

#endif // MAKEGRAPH_H
