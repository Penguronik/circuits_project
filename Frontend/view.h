#ifndef VIEW_H
#define VIEW_H

//QT
#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT
public:

    // Constructor
    explicit View(QGraphicsScene * scene, QWidget * parent = nullptr);

};

#endif // VIEW_H
