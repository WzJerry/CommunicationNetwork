#ifndef MAKEGRAPH2_H
#define MAKEGRAPH2_H
#include <QtGui>
#include <QPainter>
#include <QWidget>
#define MAX_VERTEX_NUM 20

class MakeGraph2:public QWidget
{
    Q_OBJECT

public:
    MakeGraph2(QWidget* parent =0);
    ~MakeGraph2();
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
    void deleteEdge(MGraph &m);
    void filecreate(MGraph m);
    int **recordKeyRoad;

protected:
    void paintEvent(QPaintEvent * event);

};

#endif // MAKEGRAPH_H
