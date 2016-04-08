#include "calendar.h"

Calendar::Calendar()
{
    eventListCounter = 0;
    loadEvents();

    actualDate = new QDate;
    *actualDate = QDate::currentDate();                      //get's information about current date and sets proper label
    int actualDay, actualMonth, actualYear;
    actualDate->getDate(&actualDay, &actualMonth, &actualYear);

    // essential variables initialization

    actualDate->getDate(&year,&month,&day);
    QDate dayOfWeek(year,month,1);      //gets information about first day of selected month and year
    whatDay = dayOfWeek.dayOfWeek();

    // end of essential variables initialization

    actualWeek = actualDate->weekNumber();

    // future note: array are better than days[0], days[1], days[2]... :P

    days = new Day*[7];

    days[0] = new Day("Monday");
    days[1] = new Day("Tuesday");
    days[2] = new Day("Wednesday");
    days[3] = new Day("Thursday");
    days[4] = new Day("Friday");
    days[5] = new Day("Saturday");
    days[6] = new Day("Sunday");


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


/* Signal mapper is used to send parameter to slot method. The parameter here is
 * integer which reprenets offset of certain days of week. */

    QSignalMapper* signalMapper = new QSignalMapper(this);              // signal mapping is needed to parametrize slot :(

    connect(days[0], SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(days[1], SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(days[2], SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(days[3], SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(days[4], SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(days[5], SIGNAL(pressed()), signalMapper, SLOT(map()));
    connect(days[6], SIGNAL(pressed()), signalMapper, SLOT(map()));

    signalMapper->setMapping(days[0], 0);
    signalMapper->setMapping(days[1], 1);
    signalMapper->setMapping(days[2], 2);
    signalMapper->setMapping(days[3], 3);
    signalMapper->setMapping(days[4], 4);
    signalMapper->setMapping(days[5], 5);
    signalMapper->setMapping(days[6], 6);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(scheduleDay(int)));

    colorTask();
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

    if(day>0 && day<=7)
    {
        firstDay = 1;
        determineDates(firstDay, 0);
    }
    else if(day>7 && day<=14)
    {
        firstDay = 8;
         determineDates(firstDay, 0);
    }
    else if(day>14 && day<=21)
    {
        firstDay = 15;
        determineDates(firstDay, 0);
    }
    else if(day>21 && day<=28)
    {
        firstDay = 22;
        determineDates(firstDay, 0);
    }
    else if(day>28)
        firstDay = 29;


    if( month % 2 != 0 || month == 8 ) // odd months, except August
    {
        QString days[]=     {"1-7",
                         "8-14",
                         "15-21",
                         "22-28",
                          "29-31"};
        if(day>0 && day<=7)
            currentDay = days[0];
        else if(day>7 && day<=14)
            currentDay = days[1];
        else if(day>14 && day<=21)
            currentDay = days[2];
        else if(day>21 && day<=28)
            currentDay = days[3];
        else if(day>28 && day<=31)
        {
            currentDay = days[4];
            determineDates(firstDay, 31);
        }
     }
    if( month % 2 == 0 && month != 2 && month != 8) // february
    {
        QString days[]=     {"1-7",
                         "8-14",
                         "15-21",
                         "22-28",
                          "29-30"};
        if(day>0 && day<=7)
             currentDay = days[0];
        else if(day>7 && day<=14)
             currentDay = days[1];
        else if(day>14 && day<=21)
             currentDay = days[2];
        else if(day>21 && day<=28)
             currentDay = days[3];
        else if(day>28 && day<=30)
        {
            currentDay = days[4];
            determineDates(firstDay, 30);
        }
    }
    if ( month == 2)    // even months
    {
        if ( (year % 4 == 0 & year % 100 == 0) | year % 400 == 0 )
        {
            QString days[]=     {"1-7",
                             "8-14",
                             "15-21",
                             "22-28","29"};
            if(day>0 && day<=7)
                currentDay = days[0];
            else if(day>7 && day<=14)
                currentDay = days[1];
            else if(day>14 && day<=21)
                currentDay = days[2];
            else if(day>21 && day<=28)
                currentDay = days[3];
            else if(day == 29)
            {
                currentDay = days[4];
                determineDates(firstDay, 29);
            }
        }
        else
        {
            QString days[]=     {"1-7",
                             "8-14",
                             "15-21",
                             "22-28"};
            if(day>0 && day<=7)
                currentDay = days[0];
            else if(day>7 && day<=14)
                currentDay = days[1];
            else if(day>14 && day<=21)
                currentDay = days[2];
            else if(day>21 && day<=28)
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

   if(day>7)
       day = day - 7;
   else if(month>1)
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
    days[0]->show();
    days[1]->show();
    days[2]->show();
    days[3]->show();
    days[4]->show();
    days[5]->show();
    days[6]->show();
   }

   currentDateLabel = dateToString(day,month,year);
   dateLabel->setText("<center>" + currentDateLabel + "</center>");

   actualWeek=actualWeek-1;

   sortButtons();

   colorTask();
   // setting day dates



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
    if(month==2 && year%4==0 && day>22 && flagFeb==1)
    {
        day = 29;
        flagFeb = 0;
    }
    else if(day<=22 && flagFeb==0)
         day = day + 7;
    else if (month<12)
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
    if(flagHide==1)
    {
        days[0]->show();
        days[1]->show();
        days[2]->show();
        days[3]->show();
        days[4]->show();
        days[5]->show();
        days[6]->show();
    }
    currentDateLabel = dateToString(day,month,year);
    dateLabel->setText("<center>" + currentDateLabel + "</center>");

    actualWeek=actualWeek+1;

    colorTask();

    sortButtons();

    // setting day dates

}


/* This method is slot for day-buttons clicked() signal. It takes dayID argument
 * which is offset of certain days of week. Main job of this method is to create
 * window with controls/widgets which enable adding new taks and showing list of
 * already added tasks. */
void Calendar::scheduleDay(int dayID)
{
    // Creation of interface widgets

    createWindow = new QWidget();

    taskLayout = new QGridLayout();
    taskNameLabel = new QLabel("Task:");
    taskStartTimeLabel = new QLabel("Start:");
    taskEndTimeLabel = new QLabel("Finish:");
    taskNameList = new QLabel[1];                           // array of labels for task description... similiar below
    taskStartTimeList = new QLabel[1];
    taskEndTimeList = new QLabel[1];
    taskIn = new QLineEdit;
    startTime = new QTimeEdit;
    endTime = new QTimeEdit;
    taskAccept = new QPushButton("Ok");

    taskIn->text();

    // Creation of interface layout. Numbers represent position of widget in layout grid.

    taskLayout->addWidget(taskNameLabel, 1, 1);
    taskLayout->addWidget(taskStartTimeLabel, 1, 2);
    taskLayout->addWidget(taskEndTimeLabel, 1, 3);
    taskLayout->addWidget(taskIn, 2, 1);
    taskLayout->addWidget(startTime, 2, 2);
    taskLayout->addWidget(endTime, 2, 3);
    taskLayout->addWidget(taskAccept, 2, 4);

    scrollArea = new QScrollArea;

    scrollAreaLayout = new QGridLayout;

    scrollArea->setWidgetResizable(true);

    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setLayout(scrollAreaLayout);

    taskLayout->addWidget(scrollArea, 3, 1, 1, 3);

    createWindow->setWindowTitle("Add new task");
    createWindow->setLayout(taskLayout);
    createWindow->show();

    connect(taskAccept, SIGNAL(clicked(bool)),this,SLOT(makeList()));   // acceptation of entered data
    connect(taskAccept,SIGNAL(clicked(bool)),this,SLOT(colorTask()));  // sets mark at the day with task

    // determining clicked day

    int additionalVariable;

    if(dayID + 1 >= whatDay)
        additionalVariable = -whatDay;
    else
        additionalVariable = 7 - whatDay;

    activeDate = new QDate(year, month, firstDay + dayID + additionalVariable + 1);                   // date of clicked day


    updateTaskWindow();
}

/* This is slot method for accept-button. It creates Event objects
 * which parameters are based on entered data. */
void Calendar::makeList()
{
    Event **eventListMemory;

    if(eventListCounter > 0)
        eventListMemory = eventList;

    eventList = new Event*[eventListCounter + 1];                 // array of pointers to Event objects
                                                                 // different than future situation of loading from file
    if(eventListCounter > 0)
    {
        for(int i = 0; i < eventListCounter; i++)
        {
            eventList[i] = eventListMemory[i];
        }

        delete[] eventListMemory;
    }

    eventList[eventListCounter++] = new Event(taskIn->text(), startTime->time(), endTime->time(), *activeDate);

    updateTaskWindow();     // there's need to update task list display just after adding new task
}

/* Method which displays list of tasks. Whole operation consists in
 * comparing dates of all Event objects in eventList to date of clicked
 * day of week. If dates are equal, correspoding Event objects are displayed
 * using labels. */

void Calendar::updateTaskWindow()
{

    static int licznikUpdatow;
    licznikUpdatow++;


    taskCounter = 0; // counter of correct date comparisons, also index of labels

    for(int i = 0; i < eventListCounter; i++)
    {
        if(eventList[i]->getDate() ==  *activeDate)
        {
            QString tempName;
            tempName = eventList[i]->getName();

            QString tempStartTime;
            tempStartTime = eventList[i]->getStartTime().toString("hh:mm"); // "hh:mm" is format of string to be created

            QString tempEndTime;
            tempEndTime = eventList[i]->getEndTime().toString("hh:mm");

            // rewriting smaller array to bigger one

            QLabel *taskNameListMemory;
            QLabel *taskStartTimeListMemory;
            QLabel *taskEndTimeListMemory;

            if(taskCounter > 0)
            {
                taskNameListMemory = taskNameList;
                taskStartTimeListMemory = taskStartTimeList;
                taskEndTimeListMemory = taskEndTimeList;

                taskNameList = new QLabel[taskCounter + 1];
                taskStartTimeList = new QLabel[taskCounter + 1];
                taskEndTimeList = new QLabel[taskCounter + 1];

                for(int i = 0; i < taskCounter; i++)
                {
                    taskNameList[i].setText(taskNameListMemory[i].text());
                    taskStartTimeList[i].setText(taskStartTimeListMemory[i].text());
                    taskEndTimeList[i].setText(taskEndTimeListMemory[i].text());
                }

                delete[] taskNameListMemory;
                delete[] taskStartTimeListMemory;
                delete[] taskEndTimeListMemory;
            }

            // setting most current labels

            taskNameList[taskCounter].setText(tempName);
            taskStartTimeList[taskCounter].setText(tempStartTime);
            taskEndTimeList[taskCounter].setText(tempEndTime);

            taskCounter++;

        }
    }

    removeLayout(scrollAreaLayout);     // removing all widgets in layout

    // adding all necessary labels to visualize tasks associated with active day

    for(int i = 0; i < taskCounter; i++)
    {
        scrollAreaLayout->addWidget(&taskNameList[i], i + 1, 1);
        scrollAreaLayout->addWidget(&taskStartTimeList[i], i + 1, 2);
        scrollAreaLayout->addWidget(&taskEndTimeList[i], i + 1, 3);
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
    if(whatDay==1){
        daysLayout->addWidget(days[0]);
        daysLayout->addWidget(days[1]);
        daysLayout->addWidget(days[2]);
        daysLayout->addWidget(days[3]);
        daysLayout->addWidget(days[4]);
        daysLayout->addWidget(days[5]);
        daysLayout->addWidget(days[6]);
    }
    if(whatDay==2){
        daysLayout->addWidget(days[1]);
        daysLayout->addWidget(days[2]);
        daysLayout->addWidget(days[3]);
        daysLayout->addWidget(days[4]);
        daysLayout->addWidget(days[5]);
        daysLayout->addWidget(days[6]);
        daysLayout->addWidget(days[0]);


    }
    if(whatDay==3){
        daysLayout->addWidget(days[2]);
        daysLayout->addWidget(days[3]);
        daysLayout->addWidget(days[4]);
        daysLayout->addWidget(days[5]);
        daysLayout->addWidget(days[6]);
        daysLayout->addWidget(days[0]);
        daysLayout->addWidget(days[1]);
    }
    if(whatDay==4){
        daysLayout->addWidget(days[3]);
        daysLayout->addWidget(days[4]);
        daysLayout->addWidget(days[5]);
        daysLayout->addWidget(days[6]);
        daysLayout->addWidget(days[0]);
        daysLayout->addWidget(days[1]);
        daysLayout->addWidget(days[2]);
    }
    if(whatDay==5){
        daysLayout->addWidget(days[4]);
        daysLayout->addWidget(days[5]);
        daysLayout->addWidget(days[6]);
        daysLayout->addWidget(days[0]);
        daysLayout->addWidget(days[1]);
        daysLayout->addWidget(days[2]);
        daysLayout->addWidget(days[3]);
    }
    if(whatDay==6){
        daysLayout->addWidget(days[5]);
        daysLayout->addWidget(days[6]);
        daysLayout->addWidget(days[0]);
        daysLayout->addWidget(days[1]);
        daysLayout->addWidget(days[2]);
        daysLayout->addWidget(days[3]);
        daysLayout->addWidget(days[4]);
    }
    if(whatDay==7){
        daysLayout->addWidget(days[6]);
        daysLayout->addWidget(days[0]);
        daysLayout->addWidget(days[1]);
        daysLayout->addWidget(days[2]);
        daysLayout->addWidget(days[3]);
        daysLayout->addWidget(days[4]);
        daysLayout->addWidget(days[5]);
    }
    //If month has 31 days, and selected range of days is greater than 28
    //Then this condition is hiding rest of buttons, setting flag to 1.
    //Flag is reseted in navigationLeftClicked and navigationRightClicked fcn.
    if( (month%2!=0 || month==8) && day>28)
    {
        if(whatDay == 1)
        {
           days[3]->hide();
           days[4]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay == 2)
        {
           days[0]->hide();
           days[4]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay == 3)
        {
           days[0]->hide();
           days[1]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay == 4)
        {
           days[0]->hide();
           days[1]->hide();
           days[2]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay == 5)
        {
           days[0]->hide();
           days[1]->hide();
           days[2]->hide();
           days[3]->hide();
           flagHide = 1;
        }
        if(whatDay == 6)
        {
           days[4]->hide();
           days[1]->hide();
           days[2]->hide();
           days[3]->hide();
           flagHide = 1;
        }
        if(whatDay == 7)
        {
           days[4]->hide();
           days[5]->hide();
           days[2]->hide();
           days[3]->hide();
           flagHide = 1;
        }
    }
    //If month has 30 days, and selected range of days is greater than 28
    //Then this condition is hiding rest of buttons, setting flag to 1.
    //Flag is reseted in navigationLeftClicked and navigationRightClicked fcn.
    if( month%2==0 && month!=2 && day>28)
    {
        if(whatDay==1)
        {
           days[2]->hide();
           days[3]->hide();
           days[4]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==2)
        {
           days[0]->hide();
           days[3]->hide();
           days[4]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==3)
        {
           days[0]->hide();
           days[1]->hide();
           days[4]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==4)
        {
           days[0]->hide();
           days[1]->hide();
           days[2]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==5)
        {
           days[0]->hide();
           days[1]->hide();
           days[2]->hide();
           days[3]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==6)
        {
           days[0]->hide();
           days[4]->hide();
           days[1]->hide();
           days[2]->hide();
           days[3]->hide();
           flagHide = 1;
        }
        if(whatDay==7)
        {
           days[1]->hide();
           days[4]->hide();
           days[5]->hide();
           days[2]->hide();
           days[3]->hide();
           flagHide = 1;
        }
    }
    //If month has 29 days, and selected range of days is greater than 28
    //Then this condition is hiding rest of buttons, setting flag to 1.
    //Flag is reseted in navigationLeftClicked and navigationRightClicked fcn.
    if(month==2 && day==29)
    {
        if(whatDay==1)
        {  days[1]->hide();
           days[2]->hide();
           days[3]->hide();
           days[4]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==2)
        {
           days[0]->hide();
           days[2]->hide();
           days[3]->hide();
           days[4]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==3)
        {
           days[0]->hide();
           days[1]->hide();
           days[3]->hide();
           days[4]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==4)
        {
           days[0]->hide();
           days[1]->hide();
           days[2]->hide();
           days[4]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==5)
        {
           days[0]->hide();
           days[1]->hide();
           days[2]->hide();
           days[3]->hide();
           days[5]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==6)
        {
           days[0]->hide();
           days[4]->hide();
           days[1]->hide();
           days[2]->hide();
           days[3]->hide();
           days[6]->hide();
           flagHide = 1;
        }
        if(whatDay==7)
        {
           days[0]->hide();
           days[1]->hide();
           days[4]->hide();
           days[5]->hide();
           days[2]->hide();
           days[3]->hide();
           flagHide = 1;
        }
  }
}
/* This functon is highliting day pushbutton if it contains tasks. */
void Calendar::colorTask()
{

    // searching for first matching event for every day in week
    for(int thisDay = 0; thisDay < 7; thisDay++)
    {
        for(int thisEvent = 0; thisEvent < eventListCounter; thisEvent++)
        {
            if(days[thisDay]->getDate() == eventList[thisEvent]->getDate())
            {
                days[thisDay]->setStyleSheet("background-color:red");
                break; // no need for further searching through eventList
            }
            else if(thisEvent == eventListCounter - 1) // no match => no color
            {
                days[thisDay]->setStyleSheet("background-color:none");
            }
        }
        // when no matching event found - erase color

    }
}
//This method is removing all widgets from layout
void Calendar::removeLayout(QLayout *layout)
{
    QLayoutItem *child;

    while(layout->count() != 0)
    {
        child = layout->takeAt(0);

        delete child->widget();
    }
}

/* This method calculates real dates for seven current day-buttons and sets
 * them into corresponding objects */
void Calendar::determineDates(int firstDay, int mode)
{

    QDate dayOfWeek(year,month,1);
    whatDay = dayOfWeek.dayOfWeek();

    if(mode == 0) // for days: 1-7, 8-14, 15-21, 22-28
    {
        int additionalVariable = whatDay - 1;
        for(int i = 0; i < 7; i++)
        {
            QDate date(year, month, firstDay + i);
            days[additionalVariable]->setDate(date);

            additionalVariable = (additionalVariable + 1)%7;
        }
    }


    if(mode == 29) // for last week in 29-days february
    {
        int additionalVariable = whatDay - 1;
        for(int i = 0; i < 1; i++)
        {
            QDate date(year, month, firstDay + i);
            days[additionalVariable]->setDate(date);

            additionalVariable = (additionalVariable + 1)%7;
        }

        for(int i = 0; i < 6; i++) // setting hidden buttons to neutral date, same in other modes
        {
            QDate date(1, 1, 1);
            days[additionalVariable]->setDate(date);

            additionalVariable = (additionalVariable + 1)%7;
        }
    }

    if(mode == 30)  // for last week in 30-days months
    {
        int additionalVariable = whatDay - 1;
        for(int i = 0; i < 2; i++)
        {
            QDate date(year, month, firstDay + i);
            days[additionalVariable]->setDate(date);

            additionalVariable = (additionalVariable + 1)%7;
        }

        for(int i = 0; i < 5; i++)
        {
            QDate date(1, 1, 1);
            days[additionalVariable]->setDate(date);

            additionalVariable = (additionalVariable + 1)%7;
        }
    }

    if(mode == 31)  // for last week in 31-days months
    {
        int additionalVariable = whatDay - 1;
        for(int i = 0; i < 3; i++)
        {
            QDate date(year, month, firstDay + i);
            days[additionalVariable]->setDate(date);

            additionalVariable = (additionalVariable + 1)%7;
        }

        for(int i = 0; i < 4; i++)
        {
            QDate date(1, 1, 1);
            days[additionalVariable]->setDate(date);

            additionalVariable = (additionalVariable + 1)%7;
        }
    }
}

/* This method saves all events to file.
 * Format:
 * name
 * date
 * startTime
 * endTime
 * name
 * date
 * ...
*/
void Calendar::saveEvents()
{

    QFile file("C:/CalendarData/events.txt");
    if(file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
    {
        QTextStream eventStream(&file);
        for(int thisEvent = 0; thisEvent < eventListCounter; thisEvent++)
        {
        eventStream << eventList[thisEvent]->getName() << "\n"
        << eventList[thisEvent]->getDate().toString("dd.MM.yyyy") << "\n"
        << eventList[thisEvent]->getStartTime().toString() << "\n"
        << eventList[thisEvent]->getEndTime().toString() << "\n";
        }
    }
    file.close();
}

// This method load saved informations about events from file and recreate eventList array/vector.
void Calendar::loadEvents()
{
    QFile file("C:/CalendarData/events.txt");
    if(file.open(QFile::ReadOnly))
    {
        QTextStream eventStream(&file);
        while(!eventStream.atEnd())
        {
            QString loadedName, loadedDate, loadedStartTime, loadedEndTime;

            loadedName = eventStream.readLine();
            loadedDate = eventStream.readLine();
            loadedStartTime = eventStream.readLine();
            loadedEndTime = eventStream.readLine();

            QDate convertedDate;
            QTime convertedStartTime, convertedEndTime;

            convertedDate = QDate::fromString(loadedDate, "dd.MM.yyyy");
            convertedStartTime = QTime::fromString(loadedStartTime);
            convertedEndTime = QTime::fromString(loadedEndTime);


            Event **eventListMemory;

            if(eventListCounter > 0)
                eventListMemory = eventList;

            eventList = new Event*[eventListCounter + 1];                 // array of pointers to Event objects
                                                                         // different than future situation of loading from file
            if(eventListCounter > 0)
            {
                for(int i = 0; i < eventListCounter; i++)
                {
                    eventList[i] = eventListMemory[i];
                }

                delete[] eventListMemory;
            }

            eventList[eventListCounter++] = new Event(loadedName, convertedStartTime, convertedEndTime, convertedDate);
        }
    }
    file.close();
}

// This runs automatically when application is shutting down.
void Calendar::closeEvent(QCloseEvent *event)
{
    saveEvents();
}
Calendar::~Calendar(){}

// ###############################

void Day::setDate(QDate date)
{
    this->date = date;
}

QDate Day::getDate()
{
    return date;
}
