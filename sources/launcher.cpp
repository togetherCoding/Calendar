#include <QApplication>
#include <QtWidgets>                                        // contains all widgets - long linking time?
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget *mainWindow = new QWidget;                      // perhaps we have to create new class (e.g. Calendar) which will derive from QWidget


    QPushButton *dayOne = new QPushButton("Monday");                  // makes pointer to QPushButton class (am I right? still newb) representing days of week
    QPushButton *dayTwo = new QPushButton("Tuesday");
    QPushButton *dayThree = new QPushButton("Wednesday");
    QPushButton *dayFour = new QPushButton("Thursday");
    QPushButton *dayFive = new QPushButton("Friday");
    QPushButton *daySix = new QPushButton("Saturday");
    QPushButton *daySeven = new QPushButton("Sunday");

    QHBoxLayout *daysLayout = new QHBoxLayout;                  // horizontal layout for days

    daysLayout->addWidget(dayOne);
    daysLayout->addWidget(dayTwo);
    daysLayout->addWidget(dayThree);
    daysLayout->addWidget(dayFour);
    daysLayout->addWidget(dayFive);
    daysLayout->addWidget(daySix);
    daysLayout->addWidget(daySeven);

    // creating elements for navigation box
    QPushButton *navigationLeft = new QPushButton("<<");
    QPushButton *navigationRight = new QPushButton(">>");
    QLabel *dateLabel = new QLabel("<center>1-7 Jan 2016 (week 1)</center>");      // QLabel constructor argument won't be (of course) constant later

    QHBoxLayout *navigationLayout = new QHBoxLayout;            // horizontal layout for navigation elements

    navigationLayout->addWidget(navigationLeft);
    navigationLayout->addWidget(dateLabel);
    navigationLayout->addWidget(navigationRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;                  // vertical layout for navigation and days boxes
    mainLayout->addLayout(navigationLayout);
    mainLayout->addLayout(daysLayout);


    mainWindow->setLayout(mainLayout);

    mainWindow->show();

    return app.exec();
}
