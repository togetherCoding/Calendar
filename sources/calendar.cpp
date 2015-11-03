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
    dateLabel = new QLabel();                       // QLabel initialization

    navigationLayout = new QHBoxLayout;            // horizontal layout for navigation elements

    navigationLayout->addWidget(navigationLeft);
    navigationLayout->addWidget(dateLabel);
    navigationLayout->addWidget(navigationRight);

    *actualDate = QDate::currentDate();                      //get's information about current date and sets proper label
    int actualDay, actualMonth, actualYear;
    actualDate->getDate(&actualDay, &actualMonth, &actualYear);
    QString initialDateLabel = dateToString(actualYear, actualMonth, actualDay);
    dateLabel->setText("<center>" + initialDateLabel + "</center>");

    mainLayout = new QVBoxLayout;                  // vertical layout for navigation and days boxes
    mainLayout->addLayout(navigationLayout);
    mainLayout->addLayout(daysLayout);



    this->setLayout(mainLayout);
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
        case 0:     currentMonth = "January";
        case 1:     currentMonth = "Febuary";
        case 2:     currentMonth = "March";
        case 3:     currentMonth = "April";
        case 4:     currentMonth = "May";
        case 5:     currentMonth = "June";
        case 6:     currentMonth = "July";
        case 7:     currentMonth = "August";
        case 8:     currentMonth = "September";
        case 9:    currentMonth = "October";
        case 10:    currentMonth = "November";
        case 11:    currentMonth = "December";
    }


    QString separator = "  ";
    currentDate = currentDay + separator + separator + currentMonth + separator + QString::number(year);
    return currentDate;
}

Calendar::~Calendar(){}
