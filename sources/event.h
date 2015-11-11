#include <QString>
#include <QTime>

class Event
{
    int id;
    QString name;
    bool range;
    QTime startTime;
    QTime endTime;

public:

    Event(QString name, QTime startTime, QTime endTime);
    int getID();
    QString getName();
    bool isRange();
    QTime getStartTime();
    QTime getEndTime();
};
