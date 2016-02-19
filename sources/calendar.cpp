#include "calendar.h"

Calendar::Calendar()
{
    actualDate = new QDate;
    *actualDate = QDate::currentDate();                      //get's information about current date and sets proper label
    int actualDay, actualMonth, actualYear;
    actualDate->getDate(&actualDay, &actualMonth, &actualYear);

    dayOne = new QPushButton("Monday");
    dayTwo = new QPushButton("Tuesday");
    dayThree = new QPushButton("Wednesday");
    dayFour = new QPushButton("Thursday");
    dayFive = new QPushButton("Friday");
    daySix = new QPushButton("Saturday");
    daySeven = new QPushButton("Sunday");

    daysLayout = new QHBoxLayout;

    navigationLayout = new QHBoxLayout;            // horizontal layout for navigation elements

    // creating elements for navigation box
    navigationLeft = new QPushButton("<<");
    navigationRight = new QPushButton(">>");
    dateLabel = new QLabel();                       // QLabel initialization

    navigationLayout->addWidget(navigationLeft);
    navigationLayout->addWidget(dateLabel);
    navigationLayout->addWidget(navigationRight);

    mainLayout = new QVBoxLayout;                  // vertical layout for navigation and days boxes
    mainLayout->addLayout(navigationLayout);
    mainLayout->addLayout(daysLayout);
    this->setLayout(mainLayout);

    QString initialDateLabel = dateToString(actualYear, actualMonth, actualDay);
    dateLabel->setText("<center>" + initialDateLabel + "</center>");
    sortButtons();
    connect(navigationLeft,SIGNAL(pressed()),this,SLOT(navigationLeftClicked()));   //connects navigation buttons with action (changing day's range or month)
    connect(navigationRight,SIGNAL(pressed()),this,SLOT(navigationRightClicked()));



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
}

QString Calendar::dateToString(int day, int month, int year)
{
    /* This method gets information about real current week day, month and year (from it's parameter)
       and converts month number to word (1 to January etc.). It also gets day number, and converts
       it to string. Year is shown as a number. */
    QString currentDate,currentDay,currentMonth;

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

    if( month % 2 != 0 || month == 8 )
    {
        QString days[]=     {"1-7",
                         "8-14",
                         "15-21",
                         "22-28",
                          "29-31"};
        if(day>0 && day <=7)
        currentDay = days[0];
        if(day>7 && day <=14)
        currentDay = days[1];
        if(day>14 && day <=21)
        currentDay = days[2];
        if(day>21 && day <=28)
        currentDay = days[3];
        if(day>28 && day <=31)
        currentDay = days[4];
     }
    if( month % 2 == 0 && month != 2 && month != 8)
    {
        QString days[]=     {"1-7",
                         "8-14",
                         "15-21",
                         "22-28",
                          "29-30"};
        if(day>0 && day <=7)
        currentDay = days[0];
        if(day>7 && day <=14)
        currentDay = days[1];
        if(day>14 && day <=21)
        currentDay = days[2];
        if(day>21 && day <=28)
        currentDay = days[3];
        if(day>28 && day <=30)
        currentDay = days[4];
    }
    if ( month == 2)
    {
        if ( year % 4 == 0)
        {
            QString days[]=     {"1-7",
                             "8-14",
                             "15-21",
                             "22-28","29"};
            if(day>0 && day <=7)
            currentDay = days[0];
            if(day>7 && day <=14)
            currentDay = days[1];
            if(day>14 && day <=21)
            currentDay = days[2];
            if(day>21 && day <=28)
            currentDay = days[3];
            if(day == 29)
            currentDay = days[4];
        }
        else
        {
            QString days[]=     {"1-7",
                             "8-14",
                             "15-21",
                             "22-28"};
            if(day>0 && day <=7)
            currentDay = days[0];
            if(day>7 && day <=14)
            currentDay = days[1];
            if(day>14 && day <=21)
            currentDay = days[2];
            if(day>21 && day <=28)
            currentDay = days[3];
        }
    }
    QString separator = "  ";
    currentDate = currentDay + separator + separator + currentMonth + separator + QString::number(year);
    return currentDate;
}

void Calendar::navigationLeftClicked()
{
    /* This function is used for navigation, to reach previous range
       of days or previous month, or year. At first its getting real
       date, which is needed for initialization.*/
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
        day = 29;
   }
   else
   {
        year = year - 1;
        month = 12;
        day = 29;
   }
   /* This condition is showing weekday buttons, whenever flagHide is true.
      day buttons are hidden in sortButtons function below. */
   if(flagHide == 1)
   {
   dayOne->show();
   dayTwo->show();
   dayThree->show();
   dayFour->show();
   dayFive->show();
   daySix->show();
   daySeven->show();
   }

   currentDateLabel = dateToString(day,month,year);
   dateLabel->setText("<center>" + currentDateLabel + "</center>");

   sortButtons();
}

void Calendar::navigationRightClicked()
{
    /* This function is used for navigation, to reach future range
       of days or previous month, or year. At first its getting real
       date, which is needed for initialization.*/
    if(!flag)
    {
        actualDate->getDate(&year,&month,&day);
        flag = true;
    }
    if(month == 2 && year % 4 == 0 && day>22 && flagFeb == 1)
    {
        day = 29;
        flagFeb = 0;
    }
    else if( day <= 22 && flagFeb == 0)
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
        day = 1;
    }
    /* This condition is showing weekday buttons, whenever flagHide is true.
       day buttons are hidden in sortButtons function below. */
    if(flagHide == 1)
    {
    dayOne->show();
    dayTwo->show();
    dayThree->show();
    dayFour->show();
    dayFive->show();
    daySix->show();
    daySeven->show();
    }
    currentDateLabel = dateToString(day,month,year);
    dateLabel->setText("<center>" + currentDateLabel + "</center>");

    sortButtons();
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
void Calendar::sortButtons()
{
    /* This function is sorting buttons according to the first day
     * of selected month. At first it gets information about current date
       at the initialization of program. */
    if(!flagButton)
    {
       actualDate->getDate(&year,&month,&day);
       flagButton = true;
    }

    QDate dayOfWeek(year,month,1);      //gets information about first day of selected month and year
    whatDay = dayOfWeek.dayOfWeek();    /* Used dayOfWeek function from QDate dayOfWeek object to
                                           get infomation what day of week (monday = 1, thursday = 2 etc.)
                                           is first day of selected month */

    //Sortting buttons on the information about first day of selected month
    if(whatDay == 1){
        daysLayout->addWidget(dayOne);
        daysLayout->addWidget(dayTwo);
        daysLayout->addWidget(dayThree);
        daysLayout->addWidget(dayFour);
        daysLayout->addWidget(dayFive);
        daysLayout->addWidget(daySix);
        daysLayout->addWidget(daySeven);
    }
    if(whatDay == 2){
        daysLayout->addWidget(dayTwo);
        daysLayout->addWidget(dayThree);
        daysLayout->addWidget(dayFour);
        daysLayout->addWidget(dayFive);
        daysLayout->addWidget(daySix);
        daysLayout->addWidget(daySeven);
        daysLayout->addWidget(dayOne);


    }
    if(whatDay == 3){
        daysLayout->addWidget(dayThree);
        daysLayout->addWidget(dayFour);
        daysLayout->addWidget(dayFive);
        daysLayout->addWidget(daySix);
        daysLayout->addWidget(daySeven);
        daysLayout->addWidget(dayOne);
        daysLayout->addWidget(dayTwo);
    }
    if(whatDay == 4){
        daysLayout->addWidget(dayFour);
        daysLayout->addWidget(dayFive);
        daysLayout->addWidget(daySix);
        daysLayout->addWidget(daySeven);
        daysLayout->addWidget(dayOne);
        daysLayout->addWidget(dayTwo);
        daysLayout->addWidget(dayThree);
    }
    if(whatDay == 5){
        daysLayout->addWidget(dayFive);
        daysLayout->addWidget(daySix);
        daysLayout->addWidget(daySeven);
        daysLayout->addWidget(dayOne);
        daysLayout->addWidget(dayTwo);
        daysLayout->addWidget(dayThree);
        daysLayout->addWidget(dayFour);
    }
    if(whatDay == 6){
        daysLayout->addWidget(daySix);
        daysLayout->addWidget(daySeven);
        daysLayout->addWidget(dayOne);
        daysLayout->addWidget(dayTwo);
        daysLayout->addWidget(dayThree);
        daysLayout->addWidget(dayFour);
        daysLayout->addWidget(dayFive);
    }
    if(whatDay == 7){
        daysLayout->addWidget(daySeven);
        daysLayout->addWidget(dayOne);
        daysLayout->addWidget(dayTwo);
        daysLayout->addWidget(dayThree);
        daysLayout->addWidget(dayFour);
        daysLayout->addWidget(dayFive);
        daysLayout->addWidget(daySix);
    }
    //If month has 31 days, and selected range of days is greater than 28
    //Then this condition is hiding rest of buttons, setting flag to 1.
    //Flag is reseted in navigationLeftClicked and navigationRightClicked fcn.
    if( (month % 2 != 0 || month == 8) && day > 28)
    {
        if(whatDay == 1)
        {
           dayFour->hide();
           dayFive->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 2)
        {
           dayOne->hide();
           dayFive->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 3)
        {
           dayOne->hide();
           dayTwo->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 4)
        {
           dayOne->hide();
           dayTwo->hide();
           dayThree->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 5)
        {
           dayOne->hide();
           dayTwo->hide();
           dayThree->hide();
           dayFour->hide();
           flagHide = 1;
        }
        if(whatDay == 6)
        {
           dayFive->hide();
           dayTwo->hide();
           dayThree->hide();
           dayFour->hide();
           flagHide = 1;
        }
        if(whatDay == 7)
        {
           dayFive->hide();
           daySix->hide();
           dayThree->hide();
           dayFour->hide();
           flagHide = 1;
        }
    }
    //If month has 30 days, and selected range of days is greater than 28
    //Then this condition is hiding rest of buttons, setting flag to 1.
    //Flag is reseted in navigationLeftClicked and navigationRightClicked fcn.
    if( month % 2 == 0 && month != 2 && day > 28)
    {
        if(whatDay == 1)
        {
           dayThree->hide();
           dayFour->hide();
           dayFive->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 2)
        {
           dayOne->hide();
           dayFour->hide();
           dayFive->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 3)
        {
           dayOne->hide();
           dayTwo->hide();
           dayFive->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 4)
        {
           dayOne->hide();
           dayTwo->hide();
           dayThree->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 5)
        {
           dayOne->hide();
           dayTwo->hide();
           dayThree->hide();
           dayFour->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 6)
        {
           dayOne->hide();
           dayFive->hide();
           dayTwo->hide();
           dayThree->hide();
           dayFour->hide();
           flagHide = 1;
        }
        if(whatDay == 7)
        {
           dayTwo->hide();
           dayFive->hide();
           daySix->hide();
           dayThree->hide();
           dayFour->hide();
           flagHide = 1;
        }
    }
    //If month has 29 days, and selected range of days is greater than 28
    //Then this condition is hiding rest of buttons, setting flag to 1.
    //Flag is reseted in navigationLeftClicked and navigationRightClicked fcn.
    if( month  == 2 && day == 29)
    {
        if(whatDay == 1)
        {  dayTwo->hide();
           dayThree->hide();
           dayFour->hide();
           dayFive->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 2)
        {
           dayOne->hide();
           dayThree->hide();
           dayFour->hide();
           dayFive->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 3)
        {
           dayOne->hide();
           dayTwo->hide();
           dayFour->hide();
           dayFive->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 4)
        {
           dayOne->hide();
           dayTwo->hide();
           dayThree->hide();
           dayFive->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 5)
        {
           dayOne->hide();
           dayTwo->hide();
           dayThree->hide();
           dayFour->hide();
           daySix->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 6)
        {
           dayOne->hide();
           dayFive->hide();
           dayTwo->hide();
           dayThree->hide();
           dayFour->hide();
           daySeven->hide();
           flagHide = 1;
        }
        if(whatDay == 7)
        {
           dayOne->hide();
           dayTwo->hide();
           dayFive->hide();
           daySix->hide();
           dayThree->hide();
           dayFour->hide();
           flagHide = 1;
        }
  }
}

Calendar::~Calendar(){}
