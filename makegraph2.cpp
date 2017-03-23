#include <queue>
#include "makegraph2.h"
#include <QPen>
#include <iostream>
#include <fstream>
using namespace std;
MakeGraph2::MakeGraph2(QWidget *parent):QWidget(parent)
{

}

MakeGraph2::~MakeGraph2()
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


void MakeGraph2::CreateMGraph(MGraph &M)
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
    for(int i=0;i<numOfRoads;i++)
    {
        int m=rand()%numOfCities;
        int n=rand()%numOfCities;
        if(m!=n)
        {
            if(M.arc[m][n].weight!=1)
            {
                M.arc[m][n].weight=1;
                M.arc[n][m].weight=1;
            }
            //roadGraphMatrix[n][m]=1;
        }
    }
    ofstream ofresult("/Users/jerry/cityGraph.rtf",ios::out);
    cout << "这个在写文件" << endl;
    for(int i = 0; i < M.vexnum; i++) {
        for(int j = 0; j < M.vexnum; j++) {
            ofresult << M.arc[i][j].weight << " ";
        }
        ofresult << "\n";
    }
    ofresult.close();


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

void MakeGraph2::print(MGraph m)
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


void MakeGraph2::paintEvent(QPaintEvent *)
{


    QPainter painter(this);
    QPen pen;
    painter.setPen(pen);
    pen.setColor(Qt::blue);


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

    recordKeyRoad=new int *[numOfCities];
    if(!recordKeyRoad)
    {
        cout<<endl<<"error to make juzhen!"<<endl;
        //return false;
    }
    for(int i=0;i<numOfCities;i++)
    {
        recordKeyRoad[i]=new int[numOfCities];
    }

    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            recordKeyRoad[i][j]=0;
        }
    }
    //cout<<endl<<"numOfCiteis:"<<numOfCities<<endl;
    painter.drawPoints(pointf,numOfCities);
    QPen pen1;
    pen1.setColor(Qt::blue);
    painter.setPen(pen1);
    deleteEdge(MAP);
    //Put the keyRoad into the file.
    ofstream outfile;
    outfile.open("recordKeyRoad");
    if(outfile.is_open())
    {
        for(int i = 0; i < numOfCities;i++)
        {
            for(int j=0;j<numOfCities;j++)
            {
                if(recordKeyRoad[i][j]==1)
                {
                    outfile<<i<<"\t"<<j<<endl;
                }
            }
        }
        outfile.close();
    }
    else
    {
        cout<<"Can't open the file!"<<endl;
    }
    cout<<endl<<"after delete"<<endl;

    cout<<endl<<"---------------"<<endl<<
          "record juzhen"<<endl;
        for(int i=0;i<numOfCities;i++)
         {
             for(int j=0;j<numOfCities;j++)
             {
                 cout<<"\t"<<recordKeyRoad[i][j];
             }
             cout<<endl;
         }

    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            if(MAP.arc[i][j].weight==1&&recordKeyRoad[i][j]==0)
            {
                painter.drawLine(pointf[i].x(),pointf[i].y(),pointf[j].x(),pointf[j].y());
            }
        }
    }

    QPen pen2;
    pen2.setColor(Qt::red);
    painter.setPen(pen2);
    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            if(MAP.arc[i][j].weight==1&&recordKeyRoad[i][j]==1)     //key road which is supposed to be drawn with red
            {
                painter.drawLine(pointf[i].x(),pointf[i].y(),pointf[j].x(),pointf[j].y());
            }
        }
    }
}

/*用了广度优先搜索的思想*/
bool MakeGraph2::Connectivity_BFS(MGraph m)
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
        for(int i=0;i<m.vexnum;i++)//把与v连通并且没有被访问过的结点压进队列里面。
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

void MakeGraph2::deleteEdge(MGraph &m) {
    //实验二代码，如果去掉一条链路，剩下的邻接矩阵仍是连通的。则说明这个网络是安全的。
    bool flag = true;
    for(int i = 0; i < m.vexnum; i++) {
        for(int j = 0; j < m.vexnum; j++) {
            if(m.arc[i][j].weight == 1) {
                m.arc[i][j].weight = 0;
                m.arc[j][i].weight = 0;
                //print(MAP);
                if(!Connectivity_BFS(m)){
                    flag = false;
                    m.arc[i][j].weight=1;
                    m.arc[j][i].weight=1;
                    recordKeyRoad[i][j]=1;
                    break;
                } else {
                    m.arc[i][j].weight = 1;
                    m.arc[j][i].weight = 1;
                }

           }
        }
    }
    /*if(flag) {
        cout << "Safety" << endl;
    }else {
        cout << "Not Safety" << endl;
    }
*/
}

//void MakeGraph2::filecreate(MGraph m) {
//    ofstream ofresult("/Users/jerry/123.rtf",ios::out);
//    cout << "这个在写文件" << endl;
//    for(int i = 0; i < m.vexnum; i++) {
//        for(int j = 0; j < m.vexnum; j++) {
//            ofresult << m.arc[i][j].weight << " ";
//        }
//        ofresult << "\n";
//    }
//    ofresult.close();

//}
