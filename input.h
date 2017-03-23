#ifndef INPUT_H
#define INPUT_H

#include <QObject>
#include <QDialog>
class QPushButton;
class QLabel;

class InputDialog:public QDialog
{
    Q_OBJECT
public:
    InputDialog(QWidget *parent=0);
    ~InputDialog();
    int getNumOfCities();
    int getNumOfRoads();

private:
    QPushButton *citiesButton;
    QPushButton *roadsButton;
    QLabel *label1;
    QLabel *label2;
    QLabel *citiesLabel;
    QLabel *roadsLabel;
    int numOfCities;
    int numOfRoads;

private slots:
    void slotCities();
    void slotRoads();
};

#endif // INPUT_H
