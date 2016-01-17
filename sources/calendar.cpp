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
    actualDate->getDate(&actualDay, &actualMonth, &actualYear);
    QString initialDateLabel = dateToString(actualYear, actualMonth, actualDay);
    dateLabel->setText("<center>" + initialDateLabel + "</center>");

    connect(navigationLeft,SIGNAL(pressed()),this,SLOT(navigationLeftClicked()));   //connects navigation buttons with action (changing day's range or month)
    connect(navigationRight,SIGNAL(pressed()),this,SLOT(navigationRightClicked()));
    mainLayout = new QVBoxLayout;                  // vertical layout for navigation and days boxes
    mainLayout->addLayout(navigationLayout);
    mainLayout->addLayout(daysLayout);

    connect(dayOne,SIGNAL(pressed()),this,SLOT(scheudeleMonday()));

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

   QString initialDateLabel = dateToString(day,month,year);
   dateLabel->setText("<center>" + initialDateLabel + "</center>");
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

    QString initialDateLabel = dateToString(day,month,year);
    dateLabel->setText("<center>" + initialDateLabel + "</center>");
}

void Calendar::scheudeleMonday()
{
createWindow = new QWidget();

taskLabel = new QLabel("New task: ");
taskLayout = new QGridLayout();
taskIn = new QLineEdit;

taskIn->text();

taskLayout->addWidget(taskLabel);
taskLayout->addWidget(taskIn);

createWindow->setWindowTitle("Add new task");
createWindow->setLayout(taskLayout);
createWindow->show();
}
Calendar::~Calendar(){}
