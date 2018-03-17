#ifndef SCENEZOOM_H
#define SCENEZOOM_H
#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>

class Scenezoom: public QGraphicsView
{
  Q_OBJECT

public:
    Scenezoom(QWidget* parent = 0);
    ~Scenezoom();
    void zoomIn();
    void zoomOut();
    void wheelEvent(QWheelEvent* event);
};

#endif // SCENEZOOM_H
