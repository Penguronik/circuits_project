//HEADERS
#include "constants.h"
#include "mainwindow.h"

//QT
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) //At some point organize the #includes
{
    QApplication app(argc, argv);
    MainWindow window {};
    window.show();

    return app.exec();
}
