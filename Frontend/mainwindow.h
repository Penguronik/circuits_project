#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//HEADERS
#include "graphicscomponents.h"
#include "graphicsgates.h"
#include "graphicscircuitio.h"
#include "scene.h"
#include "view.h"
#include <QMainWindow>

//QT
#include <QWidget>
#include <QBasicTimer>

class MainWindow : public QMainWindow //Consider switching to MainWindow class inheritance when adding GUI
{
//    Q_OBJECT  Probably a good idea to look over all classes and check for possible use of Q_OBJECT, take a look at the documentation one more time to see it's benefits including the properties and slots/signals

public:

    // Constructors
    explicit MainWindow(QWidget *parent = nullptr);

private:
    Scene *scene_;
    View *view_;
};
#endif // MAINWINDOW_H
