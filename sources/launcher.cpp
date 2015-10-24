#include <QApplication>
#include <QtWidgets>                                        // contains all widgets - long linking time?
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget *mainWindow = new QWidget;                      // perhaps we have to create new class (e.g. Calendar) which will derive from QWidget

    QLabel *startLabel = new QLabel("No to zaczynamy!");

    QHBoxLayout *layout = new QHBoxLayout;                  // we could use just QBoxLayout, which is parent of QH... and QV..., but it requires defining direction anyway
    layout->addWidget(startLabel);

    mainWindow->setLayout(layout);

    mainWindow->show();

    return app.exec();
}
