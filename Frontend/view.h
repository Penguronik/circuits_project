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

    // Events
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
//    virtual void mousePressEvent(QMouseEvent *event) override;
//    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    // Public Functions
    void setDragToScroll();
    void setDragToBand();
};

#endif // VIEW_H
