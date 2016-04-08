#include <QApplication>
#include <QtWidgets>
#include <QDate>
#include <QObject>
#include "event.h"

class Day : public QPushButton
{
    Q_OBJECT

public:
    explicit Day();
    explicit Day(QString name) : QPushButton(name){}
    void setDate(QDate date);
    QDate getDate();

private:
    QDate date;
};

// ###################################
// ###################################

class Calendar : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar();
    QString dateToString(int day, int month, int year);
    void determineDates(int firstDay, int mode);
    void saveEvents(); // delete before first commit
    void loadEvents(); // delete before first commit
    ~Calendar();

private:
    Day **days;            // day buttons


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


    bool flag,flagButton,flagHide,flagFeb;

    int day,month,year;
    int whatDay;

    QTimeEdit   *startTime;
    QTimeEdit   *endTime;

    Event       **eventList;

    int         eventListCounter;
    int         taskCounter;
    int         actualWeek;
    int         firstDay;

    QScrollArea *scrollArea;

    QGridLayout *scrollAreaLayout;


private slots:
     void navigationLeftClicked();
     void navigationRightClicked();
     void scheduleDay(int dayID);
     void makeList();
     void sortButtons();
     void updateTaskWindow();
     void colorTask();
     void removeLayout(QLayout *layout);
     void closeEvent(QCloseEvent *event);

};
