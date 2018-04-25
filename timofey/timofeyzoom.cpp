#include "timofey/timofeyzoom.h"

Timofeyzoom::Timofeyzoom(QWidget* parent):QGraphicsView(parent)
{

}

void Timofeyzoom::zoomIn()
{
    scale (1.5, 1.5);
}

void Timofeyzoom::zoomOut()
{
    scale (0.75, 0.75);
}

void Timofeyzoom::wheelEvent(QWheelEvent* event)
{
    if (event->delta()>0)
        zoomIn();
    else
        zoomOut();
}

Timofeyzoom::~Timofeyzoom(){}
