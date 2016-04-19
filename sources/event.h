#include <QString>
#include <QTime>
#include <QDate>

class Event
{
    QDate date;
    QString name;
    bool range;
    QTime startTime;
    QTime endTime;

public:

    Event(QString name, QTime startTime, QTime endTime, QDate date);
    Event(QString name, QDate date);
    QDate getDate();
    QString getName();
    bool isRange();
    QTime getStartTime();
    QTime getEndTime();
};
