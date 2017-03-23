#include "mainwindow.h"
#include <QApplication>
#include "input.h"
#include "algorithmforq1.h"
#include "makegraph2.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}
