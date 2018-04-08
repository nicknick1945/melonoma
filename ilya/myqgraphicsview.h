#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QWidget>
#include <QWheelEvent>
#include <QTimeLine>

class myqgraphicsview: public QGraphicsView
{
    Q_OBJECT
public:
    int _numScheduledScalings;
    myqgraphicsview(QWidget* parent=0);
    void wheelEvent(QWheelEvent *event);
    void scalingTime(qreal x);
    void animFinished();

};

#endif // MYQGRAPHICSVIEW_H
