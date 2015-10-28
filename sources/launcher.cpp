#include <QApplication>
#include <QtWidgets>                                        // contains all widgets - long linking time?
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget *mainWindow = new QWidget;                      // perhaps we have to create new class (e.g. Calendar) which will derive from QWidget


    QPushButton *dayOne = new QPushButton("Monday");                  // makes dynamic pointer to QPushButton class (am I right? still newb) representing days of week
    QPushButton *dayTwo = new QPushButton("Tuesday");
    QPushButton *dayThree = new QPushButton("Wednesday");
    QPushButton *dayFour = new QPushButton("Thursday");
    QPushButton *dayFive = new QPushButton("Friday");
    QPushButton *daySix = new QPushButton("Saturday");
    QPushButton *daySeven = new QPushButton("Sunday");

    QHBoxLayout *layout = new QHBoxLayout;                  // we could use just QBoxLayout, which is parent of QH... and QV..., but it requires defining direction anyway

    layout->addWidget(dayOne);
    layout->addWidget(dayTwo);
    layout->addWidget(dayThree);
    layout->addWidget(dayFour);
    layout->addWidget(dayFive);
    layout->addWidget(daySix);
    layout->addWidget(daySeven);


    mainWindow->setLayout(layout);

    mainWindow->show();

    return app.exec();
}
