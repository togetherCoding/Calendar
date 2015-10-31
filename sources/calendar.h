#include <QApplication>
#include <QtWidgets>

class Calendar : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar();
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

    QVBoxLayout *mainLayout;        //layouts
    QHBoxLayout *daysLayout;
    QHBoxLayout *navigationLayout;

    QString     currentDateLabel;   //strings
};

