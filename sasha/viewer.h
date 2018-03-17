#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QAction>

class Viewer: public QGraphicsView
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();

signals:
    void changeZoom ();

public slots:
    void zoomIn();
    void zoomOut();

public:
    void wheelEvent(QWheelEvent *event);
    int count=5;
};

#endif // VIEWER_H
