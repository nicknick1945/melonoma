#include "kolya_headers/scenezoom.h"

Scenezoom::Scenezoom(QWidget* parent):QGraphicsView(parent)
{

}

void Scenezoom::zoomIn()
{
    scale (1.5, 1.5);
}

void Scenezoom::zoomOut()
{
    scale (0.75, 0.75);
}

void Scenezoom::wheelEvent(QWheelEvent* event)
{
    if (event->delta()>0)
        zoomIn();
    else
        zoomOut();
}

Scenezoom::~Scenezoom()
{

}
