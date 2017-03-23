#include "input.h"
#include <iostream>
using namespace std;
#include <QApplication>
#include <QDialog>
#include <QTextCodec>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QGridLayout>
#include <QInputDialog>
#include <QStringList>
InputDialog::InputDialog(QWidget *parent)
    : QDialog(parent)
{
        //设置窗口标题
        setWindowTitle("Input Dialog");
        //创建标签对象
        label1=new QLabel(tr("Cities"));
        label2=new QLabel(tr("Roads"));

        citiesLabel=new QLabel;
        citiesLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        roadsLabel=new QLabel;
        roadsLabel->setFrameStyle((QFrame::Panel | QFrame::Sunken));

        //创建按钮对象
        citiesButton=new QPushButton(tr("&Cities"));
        roadsButton=new QPushButton(tr("&Roads"));

        //布局管理
        QGridLayout *layout=new QGridLayout(this);
        layout->addWidget(citiesButton ,0,3);
        layout->addWidget(citiesLabel,0,2);
        layout->addWidget(label1,0,1);

        layout->addWidget(roadsButton,1,3);
        layout->addWidget(roadsLabel,1,2);
        layout->addWidget(label2,1,1);

        setLayout(layout);

        //链接信号和槽
        connect(citiesButton,SIGNAL(clicked()),this,SLOT(slotCities()));
        connect(roadsButton,SIGNAL(clicked()),this,SLOT(slotRoads()));
        exec();
        cout<<endl<<"In inputdialog ,numOfCities="<<numOfCities;
}

InputDialog::~InputDialog()
{

}

int InputDialog::getNumOfCities()
{
    return numOfCities;
}

int InputDialog::getNumOfRoads()
{
    return numOfRoads;
}

void InputDialog::slotCities()
{
    bool ok;
    //弹出整型对话输入框
////    /getInt  ( QWidget * parent, 父窗口
//    const QString & title,  窗口标题
//    const QString & label,  窗口提示
//    int value = 0,  默认值
//    int min = -2147483647,  最小值
//    int max = 2147483647,   最大值
//    int step = 1,   步进值
//    bool * ok  = 0, 哪个按钮被触发
//    Qt::WindowFlags flags = 0 )
    numOfCities=QInputDialog::getInt(this,tr("Number of Cities"),tr("please enter number"),
                                         citiesLabel->text().toInt(),0,140,1,&ok);
    if(ok){
        citiesLabel->setText(QString(tr("%1").arg(numOfCities)));
    }
    //exec();
    cout<<endl<<"in slotCities(),numOfCities="<<numOfCities;
}

void InputDialog::slotRoads()
{
    bool ok;
    //弹出整型对话输入框
////    /getInt  ( QWidget * parent, 父窗口
//    const QString & title,  窗口标题
//    const QString & label,  窗口提示
//    int value = 0,  默认值
//    int min = -2147483647,  最小值
//    int max = 2147483647,   最大值
//    int step = 1,   步进值
//    bool * ok  = 0, 哪个按钮被触发
//    Qt::WindowFlags flags = 0 )
    numOfRoads=QInputDialog::getInt(this,tr("Number of Roads"),tr("please enter number"),
                                         roadsLabel->text().toInt(),0,140,1,&ok);
    if(ok){
        roadsLabel->setText(QString(tr("%1").arg(numOfRoads)));
    }
}

