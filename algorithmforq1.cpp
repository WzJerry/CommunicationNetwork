#include "algorithmforq1.h"
#include "time.h"
#include <iostream>
using namespace std;
AlgorithmForQ1::AlgorithmForQ1()
{

}


AlgorithmForQ1::~AlgorithmForQ1()
{

}
/*
int** AlgorithmForQ1::randomRoads()
{
    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            if (i==j)
            {
                roadGraphMatrix[i][j]=1;
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
            roadGraphMatrix[m][n]=1;
        }
    }

    for(int i=0;i<numOfCities;i++)
    {
        for(int j=0;j<numOfCities;j++)
        {
            cout<<roadGraphMatrix[i][j];
        }
        cout<<endl;
    }

    return roadGraphMatrix;
}
*/
