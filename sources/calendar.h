#include <QApplication>
#include <QtWidgets>
#include <QDate>
#include <QObject>


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
    QLabel      *taskList;
    QLabel      *task1;
    QLabel      *task2;

    QVBoxLayout *mainLayout;        //layouts
    QHBoxLayout *daysLayout;
    QHBoxLayout *navigationLayout;
    QGridLayout *taskLayout;

    QString     currentDateLabel;   //strings

    QLineEdit   *taskIn;                                                    //

    QDate       *actualDate;        //date

    QWidget     *createWindow;      //window

    bool flag,flagButton;

    int day,month,year;
    int whatDay;

private slots:
     void navigationLeftClicked();
     void navigationRightClicked();
     void scheduleDay(int dayID);
     void makeList();
     void sortButtons();

};

