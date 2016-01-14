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


    QLabel      *dateLabel;         //labels
    QLabel      *taskLabel;                                                  //

    QVBoxLayout *mainLayout;        //layouts
    QHBoxLayout *daysLayout;
    QHBoxLayout *navigationLayout;
    QGridLayout *taskLayout;                                                 //

    QString     currentDateLabel;   //strings

    QLineEdit   *taskIn;                                                    //

    QDate       *actualDate;        //date

    QWidget     *createWindow;      //window


private slots:
     void navigationLeftClicked();
     void navigationRightClicked();
     void scheudeleMonday();

};

