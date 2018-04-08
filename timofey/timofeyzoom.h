#ifndef TIMOFEYZOOM_H
#define TIMOFEYZOOM_H
#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>

class Timofeyzoom: public QGraphicsView
{
  Q_OBJECT

public:
    Timofeyzoom(QWidget* parent = 0);
    ~Timofeyzoom();
    void zoomIn();
    void zoomOut();
    void wheelEvent(QWheelEvent* event);
};

#endif // TIMOFEYZOOM_H
