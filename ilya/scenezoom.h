#ifndef SCENEZOOM_H
#define SCENEZOOM_H
#include <QGraphicsView>
#include <QWheelEvent>
#include <QWidget>

class scenezoom: public QGraphicsView
{
    Q_OBJECT
public:
    scenezoom(QWidget * parent=0);
    void zoomIn();
    void zoomOut();
    void wheelEvent(QWheelEvent *event);
};

#endif // SCENEZOOM_H
