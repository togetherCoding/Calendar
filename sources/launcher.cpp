#include <QApplication>
#include <QtWidgets>                                        // contains all widgets - long linking time?
#include "calendar.h"
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Calendar *mainWindow = new Calendar;                    // instantiation of object of new class Calendar

    mainWindow->show();

    return app.exec();
}
