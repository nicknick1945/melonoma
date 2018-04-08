#include "scenezoom.h"

scenezoom::scenezoom(QWidget * parent):QGraphicsView(parent)
{

}

void scenezoom::zoomIn()
{
    scale(1.5,1.5);
}

void scenezoom::zoomOut()
{
    scale(0.75,0.75);
}

void scenezoom::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
    {
        zoomIn();
    }
    else
    {
        zoomOut();
    }
}
