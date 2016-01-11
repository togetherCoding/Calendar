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

    QVBoxLayout *mainLayout;        //layouts
    QHBoxLayout *daysLayout;
    QHBoxLayout *navigationLayout;
    QHBoxLayout *textLayout;

    QString     currentDateLabel;   //strings

    QInputDialog *taskIn;

    QDate       *actualDate;        //date

    QWindow     *createWindow;      //window


private slots:
     void navigationLeftClicked();
     void navigationRightClicked();
     void scheudeleMonday();

};

