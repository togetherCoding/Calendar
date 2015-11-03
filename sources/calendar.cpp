#include "calendar.h"


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
    dateLabel = new QLabel(currentDateLabel);      // QLabel initialization with variable

    navigationLayout = new QHBoxLayout;            // horizontal layout for navigation elements

    navigationLayout->addWidget(navigationLeft);
    navigationLayout->addWidget(dateLabel);
    navigationLayout->addWidget(navigationRight);

    actualDate->currentDate();                      //get's information about current date


    mainLayout = new QVBoxLayout;                  // vertical layout for navigation and days boxes
    mainLayout->addLayout(navigationLayout);
    mainLayout->addLayout(daysLayout);



    this->setLayout(mainLayout);
}

QString Calendar::dateToString(int day, int month, int year)
{
QString currentDate,currentDay,currentMonth;

QString days[4]=     {"1-7",
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
case 2:     currentMonth = "Febuary";
case 3:     currentMonth = "March";
case 4:     currentMonth = "April";
case 5:     currentMonth = "May";
case 6:     currentMonth = "June";
case 7:     currentMonth = "July";
case 8:     currentMonth = "August";
case 9:     currentMonth = "September";
case 10:    currentMonth = "October";
case 11:    currentMonth = "November";
case 12:    currentMonth = "December";
}


QString empty = ", ";
currentDate = QString::number(day) + empty + QString::number(month) + empty + QString::number(year);
return currentDate;
}

Calendar::~Calendar(){}
