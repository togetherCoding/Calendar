#include <QApplication>
#include <QtWidgets>

struct Date
{
short day;
enum months{JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER}month;             // or just short month   I DON'T KNOW :(
short year;
};

class Calendar : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar();
    ~Calendar();

    Date updateActualDate();

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

    QVBoxLayout *mainLayout;        //layouts
    QHBoxLayout *daysLayout;
    QHBoxLayout *navigationLayout;

    QString     currentDateLabel;   //strings

    Date        actualDate;
};

