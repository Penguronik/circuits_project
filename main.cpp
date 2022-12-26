#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window{};
    qreal width{500};
    qreal height{500};
    window.resize(width, height);
    window.show();
    return app.exec();
}
