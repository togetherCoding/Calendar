#include "event.h"

Event::Event(QString name, QTime startTime, QTime endTime, QDate date)
{
    this->name = name;
    this->startTime = startTime;
    this->endTime = endTime;
    this->date = date;
}
Event::Event(QString name, QDate date)
{
    this->name = name;
    this->date = date;
}
QDate Event::getDate()
{
    return date;
}

QString Event::getName()
{
    return name;
}

bool Event::isRange()
{
    return range;
}

QTime Event::getStartTime()
{
    return startTime;
}

QTime Event::getEndTime()
{
    return endTime;
}
