#include <QApplication>
#include <QtWidgets>
#include <QDate>
#include <QObject>
#include "event.h"


class Calendar : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar();
    QString dateToString(int day, int month, int year);

    ~Calendar();

private:
    QPushButton *dayOne;            //buttons
    QPushButton *dayTwo;
    QPushButton *dayThree;
    QPushButton *dayFour;
    QPushButton *dayFive;
    QPushButton *daySix;
    QPushButton *daySeven;
    QPushButton *navigationLeft;
    QPushButton *navigationRight;
    QPushButton *taskAccept;

    QLabel      *dateLabel;         //labels
    QLabel      *taskLabel;                                                  //
    QLabel      *taskNameList;
    QLabel      *taskStartTimeList;
    QLabel      *taskEndTimeList;
    QLabel      *taskNameLabel;
    QLabel      *taskStartTimeLabel;
    QLabel      *taskEndTimeLabel;

    QVBoxLayout *mainLayout;        //layouts
    QHBoxLayout *daysLayout;
    QHBoxLayout *navigationLayout;
    QGridLayout *taskLayout;

    QString     currentDateLabel;   //strings

    QLineEdit   *taskIn;                                                    //

    QDate       *actualDate;        //date
    QDate       *activeDate;

    QWidget     *createWindow;      //window

    QTimeEdit   *startTime;
    QTimeEdit   *endTime;

    Event       **eventList;

    int         eventListCounter;


private slots:
     void navigationLeftClicked();
     void navigationRightClicked();
     void scheduleDay(int dayID);
     void makeList();
     void updateTaskWindow();

};

