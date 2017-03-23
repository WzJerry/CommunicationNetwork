#include "makegraph3.h"
#include <queue>
#include <QPen>
#include <iostream>
#include <fstream>
using namespace std;
MakeGraph3::MakeGraph3(QWidget *parent):QWidget(parent)
{

}

MakeGraph3::~MakeGraph3()
{

}

using namespace std;
#define MAX_VERTEX_NUM 20
typedef struct
{
    int weight;
}Adj,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
    AdjMatrix arc;
    int vexnum;
}MGraph;


void MakeGraph3::CreateMGraph(MGraph &M)
{
//    cout << "请输入结点的个数:";
//    cin >> M.vexnum;
//    cout << "请输入该图的邻接矩阵:" << endl;
//    for(int i = 1; i <= M.vexnum; i++)
//    {
//        for(int j = 1; j <= M.vexnum; j++)
//        {
//            cin >> M.arc[i][j].weight;
//        }
//    }
    //随机生成临街矩阵
    M.vexnum=numOfCities;
    srand((unsigned)time(NULL));
    for(int i=0;i<M.vexnum;i++)
    {
      for(int j=0;j<M.vexnum;j++)
      {
        if(i==j)
        {
          M.arc[i][j].weight=2;
        }
        else
        {
          M.arc[i][j].weight=0;
        }
      }
    }
    for(int i=0;i<numOfRoads;)
    {
        int m=rand()%numOfCities;
        int n=rand()%numOfCities;
        if(m!=n)
        {
            if(M.arc[m][n].weight!=1)
            {
                M.arc[m][n].weight=1;
                M.arc[n][m].weight=1;
                i++;
            }
            //roadGraphMatrix[n][m]=1;
        }
    }

  /*
    for(int i = 1; i <= M.vexnum; i++) {
        for(int j = i; j <= M.vexnum; j++) {
            if(i == j) {
                M.arc[i][j].weight = 0;
            }else{
                int k;
                k = rand() % 2;
                M.arc[i][j].weight = k;
                M.arc[j][i].weight = k;
            }
        }
    }
*/
}

void MakeGraph3::print(MGraph m)
{
    cout<<endl;
    for(int i = 0; i < m.vexnum; i++)
    {
        for(int j = 0; j < m.vexnum; j++)
        {
            cout << m.arc[i][j].weight << " ";
        }
        cout<<endl;
    }
}


void MakeGraph3::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    painter.setPen(pen);
    pen.setColor(Qt::blue);

    recordKeyCity=new int[numOfCities];
    for(int i=0;i<numOfCities;i++)
    {
        recordKeyCity[i]=0;
    }

    MGraph MAP;
    CreateMGraph(MAP);
    print(MAP);

    QPointF *pointf=new QPointF[numOfCities];
    srand((unsigned)time(NULL));
    for(int i=0;i<numOfCities;i++)
    {
        int x,y;
        x=rand()%500;
        y=rand()%500;
        pointf[i].setX(x);
        pointf[i].setY(y);
    }
    //cout<<endl<<"numOfCiteis:"<<numOfCities<<endl;
    painter.drawPoints(pointf,numOfCities);
    QPen pen1;
    pen1.setColor(Qt::blue);
    painter.setPen(pen1);

    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            if(MAP.arc[i][j].weight==1)
            {
                painter.drawLine(pointf[i].x(),pointf[i].y(),pointf[j].x(),pointf[j].y());
            }
        }
    }

    deletePoint(MAP);

    //write the keyCity into file.
    ofstream outfile;
    outfile.open("recordKeyCity.txt");
    if(outfile.is_open())
    {
        for(int i=0;i<numOfCities;i++)
        {
                if(recordKeyCity[i]==1)
                {
                    outfile<<i<<"\t"<<endl;
                }

        }
        outfile.close();
    }
    else
    {
        cout<<"Can't open the file!"<<endl;
    }


    cout<<endl<<"---after delete point------"<<endl;
    for(int i=0;i<numOfCities;i++)
    {
        cout<<"\t"<<recordKeyCity[i];
    }
    QPen pen2;
    pen2.setColor(Qt::red);
    pen2.setWidth(10);
    painter.setPen(pen2);
    for(int i=0;i<numOfCities;i++)
    {
        if (recordKeyCity[i]==1)
        {
            painter.drawPoint(pointf[i].x(),pointf[i].y());
        }
    }
}

/*用了广度优先搜索的思想*/
bool MakeGraph3::Connectivity_BFS(MGraph m)
{
    queue<int> q;
    bool visa[MAX_VERTEX_NUM];//之前先初始化为false
    int count=0;
    memset(visa,0,sizeof(visa));
    q.push(1);
    while(!q.empty())
    {
        int v=q.front();
        visa[v]=true;
        q.pop();
        count++;
        for(int i=0; i < m.vexnum;i++)//把与v连通并且没有被访问过的结点压进队列里面。
        {
            if(m.arc[v][i].weight)
                if(!visa[i])
                {
                    q.push(i);
                    visa[i]=true;//标志被访问过。
                }
        }
    }
    if(count==m.vexnum)//如果压进栈的结点个数刚好等于总结点的个数，则连通。
        return true;
    return false;
}

void MakeGraph3::deletePoint(MGraph m) {
    //实验三代码，去掉一个城市，如果剩下的邻接矩阵不连通，则说明这个城市需要交换机。
    int p, q;
    MGraph m_1;
    m_1.vexnum = m.vexnum - 1;
    for(int k = 0; k < m.vexnum; k++)
    {
        for(int i = 0, p = 0; i < m.vexnum; i++)
        {
            if(i == k)
            {
                continue;
            }
            else
            {
                for(int j = 0, q = 0; j < m.vexnum; j++)
                {
                    if(j == k)
                    {
                        continue;
                    }
                    else
                    {
                        m_1.arc[p][q] = m.arc[i][j];
                        q++;
                    }
                }
                p++;
                cout << endl;
            }
        }
        if(!Connectivity_BFS(m_1)) {
            //cout << "需要交换机的城市：" << k << endl;
            recordKeyCity[k]=1;
        }

    }
}

