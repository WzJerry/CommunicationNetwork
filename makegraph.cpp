#include "makegraph.h"
#include <QPen>
#include <iostream>
#include <fstream>
using namespace std;
MakeGraph::MakeGraph(QWidget *parent):QWidget(parent)
{

}

MakeGraph::~MakeGraph()
{

}


int** MakeGraph::randomRoads()
{
    //int numOfCities=inputDialog1.getNumOfCities();
    //int numOfRoads=inputDialog1.getNumOfRoads();
    int** roadGraphMatrix=new int *[numOfCities];
    if(!roadGraphMatrix)
    {
        cout<<endl<<"error to make juzhen!"<<endl;
        //return false;
    }
    for(int i=0;i<numOfCities;i++)
    {
        roadGraphMatrix[i]=new int[numOfCities];
    }

    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            roadGraphMatrix[i][j]=0;
        }
    }

    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            if (i==j)
            {
                roadGraphMatrix[i][j]=2;
            }
        }
    }

    srand((unsigned)time(NULL));
    for(int i=0;i<numOfRoads;i++)
    {
        int m=rand()%numOfCities;
        int n=rand()%numOfCities;
        if(m!=n)
        {
            if(roadGraphMatrix[n][m]!=1)
            {
                roadGraphMatrix[m][n]=1;
            }//roadGraphMatrix[n][m]=1;
        }
    }

    /*cout<<endl<<"hanshu juzhen"<<endl;
    for(int i=0;i<numOfCities;i++)
     {
         for(int j=0;j<numOfCities;j++)
         {
             //cout<<"\t"<<roadGraphMatrix[i][j];
         }
         cout<<endl;
     }

    cout<<endl<<"---------------------------------------------------"<<endl;
*/
    return roadGraphMatrix;
}

void MakeGraph::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    painter.setPen(pen);
    pen.setColor(Qt::blue);


    //int numOfCities=MainWindow::inputDialog1.getNumOfCities();
    //int numOfRoads=MainWindow::inputDialog1.getNumOfRoads();
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

    int **roadGraphMatrix1=MakeGraph::randomRoads();
    for(int i=0;i<numOfCities;i++)
     {
         for(int j=0;j<numOfCities;j++)
         {

             cout<<"\t"<<roadGraphMatrix1[i][j];
         }
         cout<<endl;
     }

    //Union-find Algorithm
    pre=new int[numOfCities];
    rank=new int[numOfCities];
    for(int i=0;i<numOfCities;i++)
    {
        pre[i]=i;
        rank[i]=0;
    }

    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            if(roadGraphMatrix1[i][j]==1)
            {
                if(findRoot(j)==findRoot(i))
                {
                    roadGraphMatrix1[i][j]=3;//draw red line
                }
                else
                {
                    int x=findRoot(i);
                    int y=findRoot(j);
                    if(rank[x]>rank[y])
                    {
                        pre[y]=x;
                    }
                    else
                    {
                        pre[x]=y;
                        if(rank[x]==rank[y])
                            rank[y]++;
                    }
                }
            }
        }
    }

    cout<<endl<<"-----------------------------"<<endl;
    for(int i=0;i<numOfCities;i++)
     {
         for(int j=0;j<numOfCities;j++)
         {

             cout<<"\t"<<roadGraphMatrix1[i][j];
         }
         cout<<endl;
     }


    //Draw line
    //pen.setColor(Qt::black);
    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            if(roadGraphMatrix1[i][j]==1)
            {
                painter.drawLine(pointf[i].x(),pointf[i].y(),pointf[j].x(),pointf[j].y());
            }
        }
    }

    //Judge Redundancy and Draw red line
    QPen pen2;
    pen2.setColor(Qt::red);
    painter.setPen(pen2);
    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            if(roadGraphMatrix1[i][j]==3)
            {
                painter.drawLine(pointf[i].x(),pointf[i].y(),pointf[j].x(),pointf[j].y());
            }
        }
    }

    //put redundancy information into file
    ofstream outfile;
    outfile.open("redundancy.txt");
    if(outfile.is_open())
    {
        for(int i=0;i<numOfCities;i++)
        {
            for(int j=0;j<numOfCities;j++)
            {
                if(roadGraphMatrix1[i][j]==3)
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


}


//Union-find Algorithm
/*void MakeGraph::judgeRedundancy(int **roadGraphMatrix1)
{
    int *pre=new int[numOfCities];
    for(int i=0;i<numOfCities;i++)
    {
        pre[i]=-1;
    }
    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            if(roadGraphMatrix1[i][j]==1)
            {
                if(findRoot(j)==findRoot(i))
                {
                    roadGraphMatrix[i][j]=3;//draw red line
                }
                else
                {
                    pre[j]=i;
                }
            }
        }
    }


}
*/


int MakeGraph::findRoot(int x)
{
    int r=x;
    while(pre[r]!=r)
    {
        r=pre[r];
    }

    int i=x,j;
    while(i!=r)
    {
        j=pre[i];
        pre[i]=r;
        i=j;
    }

    return r;       //x is the root
}

