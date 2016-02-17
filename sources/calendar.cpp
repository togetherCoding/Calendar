#include "calendar.h"

static bool flag;
static int day,month,year;

Calendar::Calendar()
{
    dayOne = new QPushButton("Monday");
    dayTwo = new QPushButton("Tuesday");
    dayThree = new QPushButton("Wednesday");
    dayFour = new QPushButton("Thursday");
    dayFive = new QPushButton("Friday");
    daySix = new QPushButton("Saturday");
    daySeven = new QPushButton("Sunday");

    daysLayout = new QHBoxLayout;

    daysLayout->addWidget(dayOne);
    daysLayout->addWidget(dayTwo);
    daysLayout->addWidget(dayThree);
    daysLayout->addWidget(dayFour);
    daysLayout->addWidget(dayFive);
    daysLayout->addWidget(daySix);
    daysLayout->addWidget(daySeven);


    // creating elements for navigation box
    navigationLeft = new QPushButton("<<");
    navigationRight = new QPushButton(">>");
    dateLabel = new QLabel();                       // QLabel initialization

    navigationLayout = new QHBoxLayout;            // horizontal layout for navigation elements

    navigationLayout->addWidget(navigationLeft);
    navigationLayout->addWidget(dateLabel);
    navigationLayout->addWidget(navigationRight);

    actualDate = new QDate;
    *actualDate = QDate::currentDate();                      //get's information about current date and sets proper label
    int actualDay, actualMonth, actualYear;
    actualDate->getDate(&actualYear, &actualMonth, &actualDay);

    QString initialDateLabel = dateToString(actualDay, actualMonth, actualYear);
    dateLabel->setText("<center>" + initialDateLabel + "</center>");

    connect(navigationLeft,SIGNAL(pressed()),this,SLOT(navigationLeftClicked()));   //connects navigation buttons with action (changing day's range or month)
    connect(navigationRight,SIGNAL(pressed()),this,SLOT(navigationRightClicked()));
    mainLayout = new QVBoxLayout;                  // vertical layout for navigation and days boxes
    mainLayout->addLayout(navigationLayout);
    mainLayout->addLayout(daysLayout);

    this->setLayout(mainLayout);

    QSignalMapper* signalMapper = new QSignalMapper(this);              // signal mapping is needed to parametrize slot :(

    connect(dayOne, SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(dayTwo, SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(dayThree, SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(dayFour, SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(dayFive, SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(daySix, SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(daySeven, SIGNAL(pressed()), signalMapper, SLOT(map()));

    signalMapper->setMapping(dayOne, 0);
    signalMapper->setMapping(dayTwo, 1);
    signalMapper->setMapping(dayThree, 2);
    signalMapper->setMapping(dayFour, 3);
    signalMapper->setMapping(dayFive, 4);
    signalMapper->setMapping(daySix, 5);
    signalMapper->setMapping(daySeven, 6);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(scheduleDay(int)));

    eventList = new Event*[100];             // constant number of events [ temporary ]
    eventListCounter = 0;

    actualDate->getDate(&year,&month,&day);
}

QString Calendar::dateToString(int day, int month, int year)
{
    QString currentDate,currentDay,currentMonth;

    QString days[]=     {"1-7",
                         "8-15",
                         "16-23",
                         "24-31"};
    if(day>0 && day <=7)
        currentDay = days[0];
    if(day>7 && day <=15)
        currentDay = days[1];
    if(day>16 && day <=23)
        currentDay = days[2];
    if(day>24 && day <=31)
        currentDay = days[3];


    switch (month)
    {
        case 1:     currentMonth = "January";
        break;
        case 2:     currentMonth = "Febuary";
        break;
        case 3:     currentMonth = "March";
        break;
        case 4:     currentMonth = "April";
        break;
        case 5:     currentMonth = "May";
        break;
        case 6:     currentMonth = "June";
        break;
        case 7:     currentMonth = "July";
        break;
        case 8:     currentMonth = "August";
        break;
        case 9:     currentMonth = "September";
        break;
        case 10:    currentMonth = "October";
        break;
        case 11:    currentMonth = "November";
        break;
        case 12:    currentMonth = "December";
        break;
        default: currentMonth = "Wrong month";
        break;
    }

    QString separator = "  ";
    currentDate = currentDay + separator + separator + currentMonth + separator + QString::number(year);
    return currentDate;
}

void Calendar::navigationLeftClicked()
{

   if(!flag)
   {
      actualDate->getDate(&year,&month,&day);
      flag = true;
   }

   if( day > 7 )
       day = day - 7;
   else if(month > 1)
   {
        month = month - 1;
        day = 28;
   }
   else
   {
        year = year - 1;
        month = 12;
   }

   currentDateLabel = dateToString(day,month,year);
   dateLabel->setText("<center>" + currentDateLabel + "</center>");
}

void Calendar::navigationRightClicked()
{

    if(!flag)
    {
        actualDate->getDate(&year,&month,&day);
        flag = true;
    }

    if( day < 22)
        day = day + 7;
    else if (month < 12)
    {
        month = month + 1;
        day = 1;
    }
    else
    {
        year = year +1;
        month = 1;
    }

    currentDateLabel = dateToString(day,month,year);
    dateLabel->setText("<center>" + currentDateLabel + "</center>");
}

void Calendar::scheduleDay(int dayID)
{

    qDebug() << year << " " << month << " " << day << " " << dayID;

    createWindow = new QWidget();

    taskLayout = new QGridLayout();
    taskNameLabel = new QLabel("Task:");
    taskStartTimeLabel = new QLabel("Start:");
    taskEndTimeLabel = new QLabel("Finish:");
    taskNameList = new QLabel[5];
    taskStartTimeList = new QLabel[5];
    taskEndTimeList = new QLabel[5];
    taskIn = new QLineEdit;
    startTime = new QTimeEdit;
    endTime = new QTimeEdit;
    taskAccept = new QPushButton("Ok");


    taskIn->text();

    taskLayout->addWidget(taskNameLabel, 1, 1);
    taskLayout->addWidget(taskStartTimeLabel, 1, 2);
    taskLayout->addWidget(taskEndTimeLabel, 1, 3);
    taskLayout->addWidget(taskIn, 2, 1);
    taskLayout->addWidget(startTime, 2, 2);
    taskLayout->addWidget(endTime, 2, 3);
    taskLayout->addWidget(taskAccept, 2, 4);

    taskLayout->addWidget(&taskNameList[0], 3, 1);
    taskLayout->addWidget(&taskNameList[1], 4, 1);
    taskLayout->addWidget(&taskNameList[2], 5, 1);
    taskLayout->addWidget(&taskNameList[3], 6, 1);
    taskLayout->addWidget(&taskNameList[4], 7, 1);

    taskLayout->addWidget(&taskStartTimeList[0], 3, 2);
    taskLayout->addWidget(&taskStartTimeList[1], 4, 2);
    taskLayout->addWidget(&taskStartTimeList[2], 5, 2);
    taskLayout->addWidget(&taskStartTimeList[3], 6, 2);
    taskLayout->addWidget(&taskStartTimeList[4], 7, 2);

    taskLayout->addWidget(&taskEndTimeList[0], 3, 3, 1, 2);
    taskLayout->addWidget(&taskEndTimeList[1], 4, 3, 1, 2);
    taskLayout->addWidget(&taskEndTimeList[2], 5, 3, 1, 2);
    taskLayout->addWidget(&taskEndTimeList[3], 6, 3, 1, 2);
    taskLayout->addWidget(&taskEndTimeList[4], 7, 3, 1, 2);


    createWindow->setWindowTitle("Add new task");
    createWindow->setLayout(taskLayout);
    createWindow->show();

    connect(taskAccept, SIGNAL(clicked(bool)),this,SLOT(makeList()));

    activeDate = new QDate(year, month, day + dayID);
    updateTaskWindow();

}
void Calendar::makeList()
{

    eventList[eventListCounter++] = new Event(taskIn->text(), startTime->time(), endTime->time(), *activeDate);

    updateTaskWindow();
}

void Calendar::updateTaskWindow()
{
    int taskCounter = 0;

    for(int i = 0; i < eventListCounter; i++)
    {

        if(eventList[i]->getDate() ==  *activeDate)
        {
            QString tempName;
            tempName = eventList[i]->getName();

            QString tempStartTime;
            tempStartTime = eventList[i]->getStartTime().toString("hh:mm");

            QString tempEndTime;
            tempEndTime = eventList[i]->getEndTime().toString("hh:mm");

            taskNameList[taskCounter].setText(tempName);
            taskStartTimeList[taskCounter].setText(tempStartTime);
            taskEndTimeList[taskCounter].setText(tempEndTime);

            taskCounter++;
        }
    }

}

Calendar::~Calendar(){}
