#include "event.h"

Event::Event(QString name, QTime startTime, QTime endTime)
{
    this->name = name;
    this->startTime = startTime;
    this->endTime = endTime;
}

int Event::getID()
{
    return id;
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
    return startTime;
}
