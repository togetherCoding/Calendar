#include "calendar.h"

Calendar::Calendar()
{
    currentDateLabel = "<center>1-7 Jan 2016 (week 1)</center>";

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

    mainLayout = new QVBoxLayout;                  // vertical layout for navigation and days boxes
    mainLayout->addLayout(navigationLayout);
    mainLayout->addLayout(daysLayout);

    this->setLayout(mainLayout);
}
Calendar::~Calendar(){}
