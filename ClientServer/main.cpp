#include <QApplication>
#include "openclientserverwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    OpenClientServerWidget wgt;

    wgt.show();

    return app.exec();
}

